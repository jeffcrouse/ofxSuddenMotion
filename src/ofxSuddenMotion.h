#pragma once

#include "ofMain.h"

//currently we only support os x 
#ifdef TARGET_OSX
#include "unimotion.h"

#define OFX_SM_RAW		0
#define OFX_SM_REAL		1
#define OFX_SM_SCALED	2

class ofxSuddenMotion{

	public:
	
	//--------------------------------
	ofxSuddenMotion();
	
	//most important calls
	int  setupHardware();
	bool readMotion();
	
	//getters 
	ofPoint getXYZ();
	ofPoint getSmoothedXYZ();
	string getHardwareName();	
	bool getHardwareAvailable();
	int getValueMode();
	
	//setters
	void setVerbose(bool _bVerbose);
	void setValueMode(int _valueMode);	
	void storeOffset();	
	void storeOffset(float xIn, float yIn, float zIn);
	void clearOffset();
	void setSmoothPct(float pct);
	
	//public properties
	double x;
	double y;
	double z;
	
	double smoothX;
	double smoothY;
	double smoothZ;
	
	protected:
	
		//protected properties
		bool bHasHardware;
		bool bVerbose;
		string hardwareName;

		int hardwareType;
		int valueMode;
		
		float smoothPct;
	
		double actualX;
		double actualY;
		double actualZ;
		
		double offsetX;
		double offsetY;
		double offsetZ;		
	
};

#endif