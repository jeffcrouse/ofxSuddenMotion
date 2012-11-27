#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	sms.setVerbose(true);
	sms.setupHardware();
	sms.setValueMode(OFX_SM_SCALED);
	sms.setSmoothPct(0.90);
	
	ofSetVerticalSync(true);
	ofSetCircleResolution(64);
}

//--------------------------------------------------------------
void testApp::update(){
	//call to read the sms data from sensor
	sms.readMotion();
	
	//get the smoothed data as an ofPoint
	ofPoint smoothed = sms.getSmoothedXYZ();
	
	printf("smoothed (x,y,z) = ( %2.2f, %2.2f, %2.2f )\n", smoothed.x, smoothed.y, smoothed.z);
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetHexColor(0x550055);
    
	string valueMode = "value type is: ";
	switch (sms.getValueMode() ) {
		case OFX_SM_SCALED:
			valueMode += "OFX_SM_SCALED";
			break;
		case OFX_SM_REAL:
			valueMode += "OFX_SM_REAL";
			break;
		case OFX_SM_RAW:
			valueMode += "OFX_SM_RAW";
			break;
	}
	
	ofDrawBitmapString("machine type is: "+sms.getHardwareName(), 10, 15);
	ofDrawBitmapString(valueMode, 10, 34);
	ofDrawBitmapString("x is "+ofToString(sms.x, 2)+"\n" + "y is "+ofToString(sms.y, 2)+ "\nz is "+ofToString(sms.z, 2), 10, 60);
	ofDrawBitmapString("SPACEBAR sets motion relative to current position!   'C' key to clear it", 10, ofGetHeight() - 15);
	
	//lets draw a circle that is controlled by x and y
	ofSetHexColor(0xDD11FF);
	ofCircle(3.0 * sms.smoothX + ofGetWidth()/2, ofGetHeight()/2, 100 + sms.smoothY*0.6);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	if(key == ' '){
		sms.storeOffset();
	}else if(key == 'c'){
		sms.clearOffset();
	}
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}