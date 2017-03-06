#StageController

Authors:

    Peter Polidoro <polidorop@janelia.hhmi.org>

License:

    BSD

[Examples](./examples)

##API

```json
{
  "id":"getApi",
  "result":{
    "firmware":["StageController"],
    "functions":[
      "dispensePellet",
      "enableDispenser",
      "disableDispenser",
      "homeStage",
      "stageHoming",
      "stageHomed",
      "moveStageTo",
      "getStagePositions"
    ],
    "parameters":[
      "stage_positions"
    ],
    "properties":[],
    "callbacks":[]
  }
}
```

##More Detailed Modular Device Information

[modular-devices](https://github.com/janelia-modular-devices/modular-devices)

##Install Library Dependencies

[arduino-libraries](https://github.com/janelia-arduino/arduino-libraries)
