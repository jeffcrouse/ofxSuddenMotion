#include "ofxSuddenMotion.h"

#ifdef TARGET_OSX

//--------------------------------
ofxSuddenMotion::ofxSuddenMotion(){
	bHasHardware	= false;
	hardwareType	= 0;
	bVerbose		= false;
	hardwareName	= "unknown";
	
	x				= 0;
	y				= 0;
	z				= 0;
	
	actualX			= 0;
	actualY			= 0;
	actualZ			= 0;
	
	smoothX			= 0.0;
	smoothY			= 0.0;
	smoothZ			= 0.0;
	
	offsetX			= 0.0;
	offsetY			= 0.0;
	offsetZ			= 0.0;		
	
	smoothPct		= 0.9;
	
	valueMode		= OFX_SM_SCALED;
}

//--------------------------------
ofPoint ofxSuddenMotion::getXYZ(){
	return ofPoint(x, y, z);
}
	
//--------------------------------
ofPoint ofxSuddenMotion::getSmoothedXYZ(){
	return ofPoint(smoothX, smoothY, smoothZ);
}

//--------------------------------
string ofxSuddenMotion::getHardwareName(){
	return hardwareName;
}

//--------------------------------
bool ofxSuddenMotion::getHardwareAvailable(){
	return bHasHardware;
}

//--------------------------------
int ofxSuddenMotion::getValueMode(){
	return valueMode;
}

//--------------------------------
void ofxSuddenMotion::setVerbose(bool _bVerbose){
	bVerbose = _bVerbose;
}

//--------------------------------
void ofxSuddenMotion::setValueMode(int _valueMode){
	valueMode = _valueMode;
	smoothX	  = 0.0;
	smoothY	  = 0.0;
	smoothZ	  = 0.0;
	
	clearOffset();
}

//--------------------------------
void ofxSuddenMotion::storeOffset(){
	offsetX = actualX;
	offsetY = actualY;
	offsetZ = actualZ;
}

//--------------------------------
void ofxSuddenMotion::storeOffset(float xIn, float yIn, float zIn){
	offsetX = xIn;
	offsetY = yIn;
	offsetZ = zIn;
}	

//--------------------------------
void ofxSuddenMotion::clearOffset(){
	storeOffset(0,0,0);
}

//--------------------------------
void ofxSuddenMotion::setSmoothPct(float pct){
	pct = MAX(0, pct);
	pct = MIN(1, pct);
	
	smoothPct = pct;
}

//--------------------------------
int ofxSuddenMotion::setupHardware(){
	
	hardwareType = detect_sms();
	bHasHardware = hardwareType;
	
	switch ( hardwareType ) {
		case powerbook:
			hardwareName = "powerbook";
			break;
		case ibook:
			hardwareName = "ibook";
			break;
		case highrespb:
			hardwareName = "highrespb";
			break;
		case macbookpro:
			hardwareName = "macbookpro";
			break;
		default:
			hardwareName = "???";
			break;
	}

	
	if( bVerbose ){
		if(bHasHardware){
			printf("ofxSuddenMotion - found hardware: %s\n", hardwareName.c_str());
		}else{
			printf("ofxSuddenMotion - no compatible hardware found\n");
		}
	}
	
	return hardwareType;
}


//--------------------------------
bool ofxSuddenMotion::readMotion(){
	
	if(!bHasHardware){
		if(bVerbose)printf("ofxSuddenMotion - no hardware found / make sure to call setupHardware() first \n"); 		
		return false;
	}
	
	bool bRead = false;
	
	if( valueMode == OFX_SM_RAW ){
		int rawX, rawY, rawZ;
		bRead =  read_sms_raw(hardwareType, &rawX, &rawY, &rawZ);
		if(bRead){
			actualX = (double)rawX;
			actualY = (double)rawY;
			actualZ = (double)rawZ;
		}
		
	}else if(valueMode == OFX_SM_REAL){
	
		double realX, realY, realZ;
		bRead =  read_sms_real(hardwareType, &realX, &realY, &realZ);
		if(bRead){
			actualX = realX;
			actualY = realY;
			actualZ = realZ;
		}
		
	}else if(valueMode == OFX_SM_SCALED){
		
		int scaledX, scaledY, scaledZ;
		bRead =  read_sms_scaled(hardwareType, &scaledX, &scaledY, &scaledZ);
		if(bRead){
			actualX = (double)scaledX;
			actualY = (double)scaledY;
			actualZ = (double)scaledZ;
		}
		
	}else{
		if(bVerbose)printf("ofxSuddenMotion - incorrect value mode\n"); 
		return false;
	}
	
	if( bRead ){
		x = actualX - offsetX;
		y = actualY - offsetY;
		z = actualZ - offsetZ;
	
		//smooth values
		smoothX *= smoothPct;
		smoothY *= smoothPct;
		smoothZ *= smoothPct;
		smoothX += x * (1.0- smoothPct);
		smoothY += y * (1.0- smoothPct);
		smoothZ += z * (1.0- smoothPct);
	}else {
		if(bVerbose)printf("ofxSuddenMotion - problem reading sms data\n");
	}

	return bRead;
}

#endif