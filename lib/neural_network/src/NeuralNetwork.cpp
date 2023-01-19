#include "NeuralNetwork.h"
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"
#include "Arduino.h"
#include "SPIFFS.h"
#include "FS.h"
// approximate working size of our model
const int kArenaSize = 50000;

NeuralNetwork::NeuralNetwork()
{
    SPIFFS.begin();
    m_error_reporter = new tflite::MicroErrorReporter();

    m_tensor_arena = (uint8_t *)malloc(kArenaSize);
    if (!m_tensor_arena)
    {
        TF_LITE_REPORT_ERROR(m_error_reporter, "Could not allocate arena");
        return;
    }
    TF_LITE_REPORT_ERROR(m_error_reporter, "Loading model");
    Serial.println(ESP.getHeapSize());
    Serial.println(ESP.getFreeHeap());
    Serial.println(ESP.getPsramSize());
    Serial.println(ESP.getFreePsram());
    File file = SPIFFS.open("/model.bin", "r");
    size_t modelSize = file.size();
    uint8_t *model = (uint8_t *)heap_caps_malloc(modelSize, MALLOC_CAP_8BIT | MALLOC_CAP_SPIRAM);
    for (size_t i = 0; i < modelSize; i++)
    {
        model[i] = file.read();
    }
    file.close();
    SPIFFS.end();
    m_model = tflite::GetModel(model);
    // This pulls in the operators implementations we need
    m_resolver = new tflite::MicroMutableOpResolver<10>();
    m_resolver->AddConv2D();
    m_resolver->AddMaxPool2D();
    m_resolver->AddFullyConnected();
    m_resolver->AddMul();
    m_resolver->AddAdd();
    m_resolver->AddLogistic();
    m_resolver->AddReshape();
    m_resolver->AddQuantize();
    m_resolver->AddDequantize();
    m_resolver->AddSoftmax();
    Serial.println("I AM ERE");
    if (m_model->version() != TFLITE_SCHEMA_VERSION)
    {
        TF_LITE_REPORT_ERROR(m_error_reporter, "Model provided is schema version %d not equal to supported version %d.",
                             m_model->version(), TFLITE_SCHEMA_VERSION);
        return;
    }
    // Build an interpreter to run the model with.
    m_interpreter = new tflite::MicroInterpreter(
        m_model, *m_resolver, m_tensor_arena, kArenaSize, m_error_reporter);

    // Allocate memory from the tensor_arena for the model's tensors.
    TfLiteStatus allocate_status = m_interpreter->AllocateTensors();
    if (allocate_status != kTfLiteOk)
    {
        TF_LITE_REPORT_ERROR(m_error_reporter, "AllocateTensors() failed");
        return;
    }

    size_t used_bytes = m_interpreter->arena_used_bytes();
    TF_LITE_REPORT_ERROR(m_error_reporter, "Used bytes %d\n", used_bytes);

    TF_LITE_REPORT_ERROR(m_error_reporter, "Output Size %d\n", m_interpreter->outputs_size());
    // Obtain pointers to the model's input and output tensors.
    input = m_interpreter->input(0);
    output = m_interpreter->output(0);
}

NeuralNetwork::~NeuralNetwork()
{
    delete m_interpreter;
    delete m_resolver;
    free(m_tensor_arena);
    delete m_error_reporter;
}

float *NeuralNetwork::getInputBuffer()
{
    return input->data.f;
}

float *NeuralNetwork::getOutputBuffer()
{
    return output->data.f;
}

NNResult NeuralNetwork::predict()
{
    m_interpreter->Invoke();
    // work out the "best output"
    float best_score = 0;
    int best_index = -1;
    // Serial.println("Jedan");
    // Serial.println(output->data.f[0]);
    // Serial.println("Dva");
    // Serial.println(output->data.f[1]);
    // Serial.println("Background");
    // Serial.print(output->data.f[2]);
    for (int i = 0; i < 2; i++)
    {
        float score = output->data.f[i];
        if (score > best_score)
        {
            best_score = score;
            best_index = i;
        }
    }
    return {
        .score = best_score,
        .index = best_index};
}