// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include <choreograph/Choreograph.h>

#include <cinder/app/App.h>

namespace myapp {

using cinder::app::KeyEvent;

MyApp::MyApp() { }

void MyApp::setup() { }

void MyApp::update() {
  choreograph::Output<cinder::vec3> target;
  choreograph::Timeline timeline;
// Create a Motion with a Connection to target and modify
// the Motion’s underlying Sequence.
  timeline.apply( &target )
          .then<choreograph::Hold>(cinder::vec3( 1.0 ), 1.0 )
          .then<choreograph::RampTo>(cinder::vec3( 100 ), 3.0 );
  timeline.step( 1.0 / 60.0 );
}

void MyApp::draw() { }

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
