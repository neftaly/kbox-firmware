/*
  The MIT License

  Copyright (c) 2016 Thomas Sarlandie thomas@sarlandie.net

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/
#pragma once

//#include <ADC.h>
#include "TaskManager.h"
#include "KMessage.h"
#include <PID_v1.h>

//following variables will need to be tuned based on actual boat performance
#define P_Param  0.5 //proportional param P-gain, the gain determines how much change the OP will make due to a change in error
#define I_Param  0.0 //integral or I-gain, the the reset determines how much to change the OP over time due to the error
#define D_Param  0.0 //derivative or D-gain, the preact determines how much to change the OP due from a change in direction of the error
#define AUTOPILOTDEADZONE  0 //to be adjusted based on boat characteristics
#define AUTOPILOTSLACK 0 //to be adjusted based on boat characteristics
#define MAXRUDDERSWING 66.0 //max swing lock to lock

class AutoPilotTask : public Task, public KReceiver, public KVisitor, public KGenerator {  private:
    
    double apRudderSensorPosition; //populated from RudderSensorTask
    double apRudderCommandSent;
    bool sameLastDirection; //last rudder movement direction
    bool navMode = false;
    bool navDodgeMode = false;
    
  public:
    AutoPilotTask() : Task("AutoPilot") {};
    void processMessage(const KMessage& message);
    void visit(const NAVMessage&);
    void visit(const RUDMessage&);
    void loop();
};