# StageController

Authors:

    Peter Polidoro <polidorop@janelia.hhmi.org>

License:

    BSD

## Ancestors

[ModularServer](https://github.com/janelia-arduino/ModularServer)

[ModularDeviceBase](https://github.com/janelia-arduino/ModularDeviceBase)

[StepDirController](https://github.com/janelia-arduino/StepDirController)

[StepperController](https://github.com/janelia-arduino/StepperController)

## Clients

## Devices

[modular_device_base](https://github.com/janelia-modular-devices/modular_device_base.git)

[step_dir_controller](https://github.com/janelia-modular-devices/step_dir_controller.git)

[stepper_controller](https://github.com/janelia-modular-devices/stepper_controller.git)

## API

```json
{
  "id":"getApi",
  "result":{
    "firmware":["StageController"],
    "functions":[
      "homeStage",
      "stageHoming",
      "stageHomed",
      "moveStageTo",
      "moveStageSoftlyTo",
      "getStagePositions"
    ],
    "parameters":[
      "stage_positions"
    ],
    "properties":[
      "stageChannelCount",
      "stagePositionMin",
      "stagePositionMax"
    ],
    "callbacks":[]
  }
}
```

## API Verbose

```json
{
  "id":"getApiVerbose",
  "result":{
    "firmware":["StageController"],
    "functions":[
      {
        "name":"homeStage",
        "parameters":[],
        "result_info":{
          "type":"bool"
        }
      },
      {
        "name":"stageHoming",
        "parameters":[],
        "result_info":{
          "type":"bool"
        }
      },
      {
        "name":"stageHomed",
        "parameters":[],
        "result_info":{
          "type":"bool"
        }
      },
      {
        "name":"moveStageTo",
        "parameters":[
          "stage_positions"
        ],
        "result_info":{
          "type":"bool"
        }
      },
      {
        "name":"moveStageSoftlyTo",
        "parameters":[
          "stage_positions"
        ],
        "result_info":{
          "type":"bool"
        }
      },
      {
        "name":"getStagePositions",
        "parameters":[],
        "result_info":{
          "type":"array",
          "array_element_type":"double"
        }
      },
      {
        "name":"getStageTargetPositions",
        "parameters":[],
        "result_info":{
          "type":"array",
          "array_element_type":"double"
        }
      },
      {
        "name":"stageAtTargetPositions",
        "parameters":[],
        "result_info":{
          "type":"bool"
        }
      }
    ],
    "parameters":[
      {
        "name":"stage_positions",
        "type":"array",
        "array_element_type":"double"
      }
    ],
    "properties":[
      {
        "name":"stagePositionMin",
        "type":"array",
        "array_element_type":"double",
        "functions":[
          "getValue",
          "setValue",
          "getDefaultValue",
          "setValueToDefault",
          "getElementValue",
          "setElementValue",
          "getDefaultElementValue",
          "setElementValueToDefault",
          "setAllElementValues",
          "getArrayLength",
          "setArrayLength"
        ],
        "parameters":[
          "value",
          "element_index",
          "element_value",
          "array_length"
        ]
      },
      {
        "name":"stagePositionMax",
        "type":"array",
        "array_element_type":"double",
        "functions":[
          "getValue",
          "setValue",
          "getDefaultValue",
          "setValueToDefault",
          "getElementValue",
          "setElementValue",
          "getDefaultElementValue",
          "setElementValueToDefault",
          "setAllElementValues",
          "getArrayLength",
          "setArrayLength"
        ],
        "parameters":[
          "value",
          "element_index",
          "element_value",
          "array_length"
        ]
      },
      {
        "name":"stageChannelCount",
        "type":"long",
        "functions":[
          "getValue",
          "setValue",
          "getDefaultValue",
          "setValueToDefault"
        ],
        "parameters":[
          "value"
        ]
      }
    ],
    "callbacks":[]
  }
}
```

## More Detailed Modular Device Information

[modular-devices](https://github.com/janelia-modular-devices/modular-devices)

## Install Library Dependencies

[arduino-libraries](https://github.com/janelia-arduino/arduino-libraries)
