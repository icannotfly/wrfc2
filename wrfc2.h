//
// water rocket flight computer mk2
// (c) 2022 icannotfly
//

#pragma once



// code version
#define VERSION "0.2.1"
#define BUILD "56"



Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);

StateMachine sm = StateMachine();
