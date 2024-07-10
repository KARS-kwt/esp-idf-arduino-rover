set(srcs
        "main.c"
        # "AltitudeSensor.cpp"
        # "AttitudeSensor.cpp"
        "GamePad.cpp"
        "sketch.cpp"
        # "mpu9250_compass_example.cpp"
        # "arduinojson_example.cpp"
        )

set(requires "bluepad32" "bluepad32_arduino" "arduino" "btstack" "ArduinoJson")

idf_component_register(SRCS "${srcs}"
                    INCLUDE_DIRS "."
                    REQUIRES "${requires}")
