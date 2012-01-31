//
//  ofxPlaylistAEHelper.h
//  testGibson
//
//  Created by Tim Gfrerer on 20/01/2012.
//  Copyright (c) 2012 ponies & light. All rights reserved.
//

#ifndef testGibson_ofxPlaylistAEHelper_h
#define testGibson_ofxPlaylistAEHelper_h

#include "ofMain.h"
#include "ofxPlaylist.h"
#include "ofxXmlSettings.h"

/*
 
 DEPENDENCIES:		
 
 + ofxXMLSettings (standard addon)
 + ofxPlaylist 
 
 this provides a few static methods:
	
	static void rewindXML(ofxXmlSettings& XML);
	static bool pushXMLto(ofxXmlSettings& XML, string where);
	static void parseKeyframesFor(ofxXmlSettings& animXML, ofxPlaylist& tmpPlaylist, float& targetVar, int j);
 
 */


class ofxPlaylistAEHelper {
public:

	// ----------------------------------------------------------------------
	
	static void rewindXML(ofxXmlSettings& XML){
		while (XML.popTag() > 0);
	}
	
	// ----------------------------------------------------------------------
	
	static bool pushXMLto(ofxXmlSettings& XML, string where){
		// returns true if successful. ofxXMLSettings object is pushed to given depth as a side-effect.

		// begins search at current XML push depth
		// always pushes into the first given match.

		// returns false if not successful.
		
		// example input: "movie:composition,name=Comp 1:layer,index=1"

		vector<string> tags = ofSplitString(where, ":");
		
		for (int i=0; i<tags.size(); i++) {
			
			string identifier = tags[i];
			
			vector<string> tagWithAttrSpecifier = ofSplitString(identifier, ",");
			// we should always have a first element, our tag specifier:
			string tag = tagWithAttrSpecifier[0];								
			
			if (tagWithAttrSpecifier.size()==2){
				// an attribute Specifier has been set.
				
				vector<string> attrWithSearchValue = ofSplitString(tagWithAttrSpecifier[1],"=");
				
				if (attrWithSearchValue.size() == 2){
					// all is well
					
					string attrName		= attrWithSearchValue[0];
					string attrValue	= attrWithSearchValue[1];
					
					// great. so now we know:
					// tag, attrName, attrValue
					
					int tagCount = XML.getNumTags(tag);
					
					bool bFound = false;
					
					for	(int t=0; t<tagCount; t++){
						// walk through all tags and see if we can find one with the correct attribute=value.
						if (attrValue == XML.getAttribute(tag, attrName, "", t)){
							
							XML.pushTag(tag, t);
							
							bFound = true;
							// no need to continue looping.
							break;
						}
					}

					if (bFound == false){
						// we couldn't find the correct tag with attribute = value
						
						ofLog(OF_LOG_WARNING) << "We could not find the correct tag " << tag << "with attr:" << attrName << "=" << attrValue;
						return false;
					}
					
				} else {
					ofLog(OF_LOG_WARNING) << "You have not specified an attribute search value for tag: " << tag << "attribute=" << tagWithAttrSpecifier[1];
				}
				
			} else {
				// no attribute Specifier has been set.
				
				// push into the first tag with the given name.
				bool r = XML.pushTag(tag);

				// check if all went well, otherwise return false.
				if (r==false) return false;
			}
			
			
		}

		// if all went well, we have not prematurely returned false; so return true.
		return true;
	}
	
	// ----------------------------------------------------------------------
	
	static void parseKeyframesForPair(ofxXmlSettings& animXML, ofxPlaylist& tmpPlaylist, float& targetVarX, float& targetVarY, string aeXmlPropertyType, float offsetX=0, float offsetY=0){
		using namespace Playlist;
		
		if (pushXMLto(animXML,"property,type=" +  aeXmlPropertyType)){

		// we are now within the Position transorm tag
		int kC = animXML.getNumTags("key");
		
		float lastTime = 0;
		
		for (int k=0; k<kC; k++){
			
			vector<string> tmpPosValues = ofSplitString(animXML.getAttribute("key", "value", "", k), ",");
			
			float keyFrameTime = animXML.getAttribute("key", "time", 0.f, k);
			
			tmpPlaylist.addKeyFrame(Action::tween((keyFrameTime - lastTime)*1000.f, &targetVarX, ofToFloat(tmpPosValues[0]) + offsetX, TWEEN_LIN, TWEEN_EASE_IN_OUT));
			tmpPlaylist.addToKeyFrame(Action::tween((keyFrameTime - lastTime)*1000.f, &targetVarY, ofToFloat(tmpPosValues[1]) + offsetY, TWEEN_LIN, TWEEN_EASE_IN_OUT));
			
			lastTime = keyFrameTime;
			
			
#ifdef PLAYLIST_DEBUG_MODE
			ofLog(OF_LOG_VERBOSE) << "time:  " << animXML.getAttribute("key", "time", 0.f, k) << endl
			<< "anchor point: " << animXML.getAttribute("key", "value", "", k) << endl
			<< "value X: " << ofToFloat(tmpPosValues[0]) << " + offsetX: " << offsetX << endl
			<< "value Y: " << ofToFloat(tmpPosValues[1]) << " + offsetY: " << offsetY;
#endif			
		}
		animXML.popTag();	// property
		}
	}
	
	
	// ----------------------------------------------------------------------
	
	static void parseKeyframesFor(ofxXmlSettings& animXML, ofxPlaylist& tmpPlaylist, float& targetVar, string aeXmlPropertyType, float offsetVal=0){
		using namespace Playlist;
		
		if (pushXMLto(animXML,"property,type=" +  aeXmlPropertyType)){
			// we are now within the <property type="aeXmlPropertyType"> transorm tag
			int kC = animXML.getNumTags("key");
			
			float lastTime = 0;
			float lastOutSpeed=0.f;
			float lastOutInfluence=0.f;
			bool lastInterpInNonLinear = false;
			
			for (int k=0; k<kC; k++){
				
				string tmpPosValue = animXML.getAttribute("key", "value", "", k);
				if (k==0 && tmpPosValue != ""){
					// the first keyframe is not really a keyframe, it is the start value.
					// targetVar = ofToFloat(tmpPosValue);
					
					lastOutInfluence	= animXML.getAttribute("key","out_influence", 0.f, k) / 100.f;
					lastOutSpeed		= animXML.getAttribute("key","out_speed", 0.f, k);
					
					lastInterpInNonLinear = (animXML.getAttribute("key", "interp_out", "", k) != "Linear");
				}
				
				if (k>=0 && tmpPosValue != ""){
					
					float keyFrameTime = animXML.getAttribute("key", "time", 0.f, k);
					
					if (lastInterpInNonLinear || animXML.getAttribute("key", "interp_in", "", k) != "Linear"){
						BezierTween * bezTween = new BezierTween();
						bezTween->setInInfluence(lastOutInfluence);
						bezTween->setInSpeed(lastOutSpeed);
						
						float tmpOI = animXML.getAttribute("key", "in_influence", 0.f, k) / 100.f;
#ifdef PLAYLIST_DEBUG_MODE
						ofLog(OF_LOG_VERBOSE) << "in_influence   :" << tmpOI;
#endif
						bezTween->setOutInfluence(tmpOI);
						float tmpSpeed = animXML.getAttribute("key", "in_speed", 0.f, k);
						bezTween->setOutSpeed(tmpSpeed);
#ifdef PLAYLIST_DEBUG_MODE
						ofLog(OF_LOG_VERBOSE) << "in_speed       :" << tmpSpeed;
#endif
						// add bezier keyframe.
						tmpPlaylist.addKeyFrame(Action::tween((keyFrameTime - lastTime)*1000.f, &targetVar, ofToFloat(tmpPosValue ) + offsetVal, ofPtr<BezierTween>(bezTween)));
						
					} else {
						tmpPlaylist.addKeyFrame(Action::tween((keyFrameTime - lastTime)*1000.f, &targetVar, ofToFloat(tmpPosValue ) + offsetVal, TWEEN_LIN, TWEEN_EASE_IN_OUT));
					}
					
#ifdef PLAYLIST_DEBUG_MODE
					ofLog(OF_LOG_VERBOSE) << "lastOutInfluence:" << lastOutInfluence;
					ofLog(OF_LOG_VERBOSE) << "lastOutSpeed    :" << lastOutSpeed;
#endif					
					lastTime = keyFrameTime;
					lastOutInfluence	= animXML.getAttribute("key","out_influence", 0.f, k) / 100.f;
					
					lastOutSpeed		= animXML.getAttribute("key","out_speed", 0.f, k);
					
					lastInterpInNonLinear = (animXML.getAttribute("key", "interp_out", "", k) != "Linear");
					
				}

#ifdef PLAYLIST_DEBUG_MODE
				ofLog(OF_LOG_VERBOSE) << "time:  " << animXML.getAttribute("key", "time", 0.f, k)
				<< "value ("<< k << "):  " << animXML.getAttribute("key", "value", "", k)
				<< "offset: " << offsetVal;
#endif
				
			}
			animXML.popTag();	// property
		}
	};

};




#endif
