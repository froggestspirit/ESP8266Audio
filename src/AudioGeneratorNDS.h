/*
  AudioGenerator
  Base class of an audio output generator
  
  Copyright (C) 2017  Earle F. Philhower, III

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _AUDIOGENERATORNDS_H
#define _AUDIOGENERATORNDS_H

#include "AudioGenerator.h"

class AudioGeneratorNDS : public AudioGenerator
{
  public:
    AudioGeneratorNDS();
    virtual ~AudioGeneratorNDS() override;
    virtual bool begin(AudioFileSource *source, AudioOutput *output, int songID);
	virtual void decodeADPCMSample(int i,uint8_t nibble);
	virtual bool loadSong(int id);
	virtual uint8_t Cnv_Attack(uint8_t attk);//table generated from Fincs FSS
	virtual int Calc_Attack(uint8_t i, uint8_t frame);
	virtual uint16_t Cnv_Fall(uint8_t fall);//table generated from Fincs FSS
	virtual int Cnv_Sust(uint8_t sust);//table generated from Fincs FSS
	virtual int Cnv_dB(uint8_t vol);//table generated from Fincs FSS
	virtual uint16_t Cnv_Vol(int db);
	virtual uint32_t getSampleAddress(uint8_t bank,uint16_t inst);
	virtual uint32_t getAddress(uint32_t addr);
	virtual bool setInst(int i, uint8_t index);
	virtual bool setSample(int i, uint32_t address);
    virtual bool loop() override;
    virtual bool stop() override;
    virtual bool isRunning() override { return running;}
	int sampleRate;
	
	bool delayHit;
	
	int maxLoops;//number of times to loop the song before fading out
	uint8_t timesLooped[16];
	int16_t fadeVol;
	uint8_t loopi;
	bool infLoop=false;
	
	uint8_t temp[4];
	uint8_t tempKey[8];
	uint32_t temp32;
	uint8_t varLength;
	uint32_t infoBlock;
	uint32_t fatArray;
	uint32_t sseqArray;
	uint32_t sbnkArray;
	uint32_t swarArray;
	uint16_t sseqID;
	uint16_t sbnkID;
	uint16_t swarID[4];
	
	int sseqIndex;
	uint32_t sseqPointer;
	uint32_t sbnkPointer;
	uint32_t swarPointer[4];
	uint32_t sseqSize;
	uint32_t dataOffset;
	uint32_t chPointer[16];
	uint16_t usedTracks;
	uint16_t sseqTempo;
	uint16_t tempoFill;
	uint8_t sseqVol;
	
	uint8_t slotChannel[16];//sample playing in this slot belongs to what channel
	uint8_t slotFree[16];//is this slot free?
	uint8_t curSlot;
	uint32_t slotMidiFreq[16];
	uint8_t slotNote[16];
	int16_t slotNoteVel[16];
	uint32_t slotNoteLen[16];
	uint32_t chDelay[16];
	uint8_t chInstrument[16];
	uint8_t chPan[16];
	int16_t chPanL[16];
	int16_t chPanR[16];
	int16_t chVol[16];
	uint8_t chTranspose[16];
	uint8_t chPitchBend[16];
	uint8_t chPitchBendRange[16];
	uint16_t chSweepPitch[16];
	uint8_t chPriority[16];
	uint8_t chPolyMono[16];
	uint8_t chTie[16];
	uint8_t chPort[16];
	uint8_t chPortOn[16];
	uint8_t chPortTime[16];
	uint16_t chModDelay[16];
	uint8_t chModDepth[16];
	uint8_t chModSpeed[16];
	uint8_t chModType[16];
	uint8_t chModRange[16];
	uint8_t chAttack[16];
	uint8_t chDecay[16];
	uint8_t chSustain[16];
	uint8_t chRelease[16];
	uint8_t chLoopTimes[16];//times left to loop
	uint32_t chLoopOffset[16];//offset to return to from loop end marker
	uint32_t chReturnOffset[16];//offset to return to from the call
	bool chInCall[16];//track hit a call command and did not hit return yet

	uint8_t slotAttack[16];
	uint16_t slotDecay[16];
	int32_t slotSustain[16];
	uint16_t slotRelease[16];
	uint8_t slotPan[16];
	int16_t slotPanL[16];
	int16_t slotPanR[16];
	int32_t slotADSRVol[16];
	uint8_t slotADSRState[16];
	
	uint32_t instAddress[128];//address of the instrument definition for instruments 0-127
	uint8_t instType[128];
	
	int16_t volModL[16];
	int16_t volModR[16];
	int mixer[2];//pre mixer
	int16_t soundOut[2];//final output
	bool chActive[16];//is the channel on
	uint32_t slotPitch[16];
	uint32_t slotPitchFill[16];
	uint32_t samplePitch[16];
	uint32_t samplePitchFill[16];
	uint32_t sampleOffset[16];//offset of the current sample
	uint32_t samplePos[16];//current position in the sample
	uint32_t sampleEnd[16];//the end of the sample
	uint32_t sampleLoop[16];//loop point
	uint32_t sampleLoopLength[16];//length of loop point to end
	uint8_t sampleFormat[16];//format of the sample
	bool sampleLoops[16];//does the sample loop
	bool sampleDone[16];//did the non-looping sample finish
	
	bool sampleNibbleLow[16];
	uint8_t tempNibble[16];
	int8_t sampleStepIndex[16];
	int16_t sampleDiff;
	int16_t samplePredictor[16];
	int16_t sampleOutput[16];
	int16_t sampleStep[16];
	int8_t sampleStepIndexLoop[16];
	int16_t samplePredictorLoop[16];
	int16_t sampleStepLoop[16];
	int8_t sampleStepIndexStart[16];
	int16_t samplePredictorStart[16];
	int16_t sampleStepStart[16];
	uint32_t keyRoot[16*0x80];//root key for each key
	uint8_t keyBank[16*0x80];//for split key instruments
	uint16_t keySample[16*0x80];//for split key instruments
	uint8_t keyAttack[16*0x80];
	uint8_t keyDecay[16*0x80];
	uint8_t keySustain[16*0x80];
	uint8_t keyRelease[16*0x80];
	uint8_t keyPan[16*0x80];
	
	
  public:
    virtual bool RegisterMetadataCB(AudioStatus::metadataCBFn fn, void *data) { return cb.RegisterMetadataCB(fn, data); }
    virtual bool RegisterStatusCB(AudioStatus::statusCBFn fn, void *data) { return cb.RegisterStatusCB(fn, data); }

  protected:
    bool running;
    AudioFileSource *file;
    AudioOutput *output;
    int16_t lastSample[2];

  protected:
    AudioStatus cb;
};

#endif
