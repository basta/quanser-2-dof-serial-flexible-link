  function targMap = targDataMap(),

  ;%***********************
  ;% Create Parameter Map *
  ;%***********************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 11;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc paramMap
    ;%
    paramMap.nSections           = nTotSects;
    paramMap.sectIdxOffset       = sectIdxOffset;
      paramMap.sections(nTotSects) = dumSection; %prealloc
    paramMap.nTotData            = -1;
    
    ;%
    ;% Auto data (q_2dsfl_pos_cntrl_P)
    ;%
      section.nData     = 20;
      section.data(20)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_P.DTH1_LIM_ENABLE
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_pos_cntrl_P.DTH2_LIM_ENABLE
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% q_2dsfl_pos_cntrl_P.DTH2_MAX
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% q_2dsfl_pos_cntrl_P.DTH2_MIN
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% q_2dsfl_pos_cntrl_P.K1
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% q_2dsfl_pos_cntrl_P.K1_defl_b
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 8;
	
	  ;% q_2dsfl_pos_cntrl_P.K1_strain_b
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 9;
	
	  ;% q_2dsfl_pos_cntrl_P.K2
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 10;
	
	  ;% q_2dsfl_pos_cntrl_P.K2_defl_b
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 14;
	
	  ;% q_2dsfl_pos_cntrl_P.K2_strain_b
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 15;
	
	  ;% q_2dsfl_pos_cntrl_P.KE_D1
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 16;
	
	  ;% q_2dsfl_pos_cntrl_P.KE_D2
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 17;
	
	  ;% q_2dsfl_pos_cntrl_P.LIMIT_SWITCHES_ENABLE
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 18;
	
	  ;% q_2dsfl_pos_cntrl_P.RepeatingSequenceStair_OutValue
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 19;
	
	  ;% q_2dsfl_pos_cntrl_P.BiasRemoval_end_time
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 29;
	
	  ;% q_2dsfl_pos_cntrl_P.BiasRemoval_end_time_g
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 30;
	
	  ;% q_2dsfl_pos_cntrl_P.BiasRemoval_start_time
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 31;
	
	  ;% q_2dsfl_pos_cntrl_P.BiasRemoval_start_time_l
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 32;
	
	  ;% q_2dsfl_pos_cntrl_P.BiasRemoval_switch_id
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 33;
	
	  ;% q_2dsfl_pos_cntrl_P.BiasRemoval_switch_id_n
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 34;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 7;
      section.data(7)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_P.HILReadAnalog_channels
	  section.data(1).logicalSrcIdx = 20;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_pos_cntrl_P.HILWriteAnalog_channels
	  section.data(2).logicalSrcIdx = 21;
	  section.data(2).dtTransOffset = 2;
	
	  ;% q_2dsfl_pos_cntrl_P.HILReadEncoder_channels
	  section.data(3).logicalSrcIdx = 22;
	  section.data(3).dtTransOffset = 3;
	
	  ;% q_2dsfl_pos_cntrl_P.HILReadAnalog_channels_a
	  section.data(4).logicalSrcIdx = 23;
	  section.data(4).dtTransOffset = 4;
	
	  ;% q_2dsfl_pos_cntrl_P.HILWriteAnalog_channels_e
	  section.data(5).logicalSrcIdx = 24;
	  section.data(5).dtTransOffset = 6;
	
	  ;% q_2dsfl_pos_cntrl_P.HILWriteDigital_channels
	  section.data(6).logicalSrcIdx = 25;
	  section.data(6).dtTransOffset = 7;
	
	  ;% q_2dsfl_pos_cntrl_P.HILReadDigital_channels
	  section.data(7).logicalSrcIdx = 26;
	  section.data(7).dtTransOffset = 10;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
      section.nData     = 8;
      section.data(8)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_P.StopwithMessage_message_icon
	  section.data(1).logicalSrcIdx = 27;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_pos_cntrl_P.StopwithMessage1_message_icon
	  section.data(2).logicalSrcIdx = 28;
	  section.data(2).dtTransOffset = 1;
	
	  ;% q_2dsfl_pos_cntrl_P.StopwithMessage_message_icon_a
	  section.data(3).logicalSrcIdx = 29;
	  section.data(3).dtTransOffset = 2;
	
	  ;% q_2dsfl_pos_cntrl_P.StopwithMessage1_message_icon_g
	  section.data(4).logicalSrcIdx = 30;
	  section.data(4).dtTransOffset = 3;
	
	  ;% q_2dsfl_pos_cntrl_P.StopwithMessage_message_icon_c
	  section.data(5).logicalSrcIdx = 31;
	  section.data(5).dtTransOffset = 4;
	
	  ;% q_2dsfl_pos_cntrl_P.StopwithMessage1_message_icon_m
	  section.data(6).logicalSrcIdx = 32;
	  section.data(6).dtTransOffset = 5;
	
	  ;% q_2dsfl_pos_cntrl_P.StopwithMessage2_message_icon
	  section.data(7).logicalSrcIdx = 33;
	  section.data(7).dtTransOffset = 6;
	
	  ;% q_2dsfl_pos_cntrl_P.StopwithMessage3_message_icon
	  section.data(8).logicalSrcIdx = 34;
	  section.data(8).dtTransOffset = 7;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(3) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_P.LimitedCounter_uplimit
	  section.data(1).logicalSrcIdx = 35;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(4) = section;
      clear section
      
      section.nData     = 69;
      section.data(69)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_P.Constant2_Value
	  section.data(1).logicalSrcIdx = 36;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_pos_cntrl_P.Cnstant1_Value
	  section.data(2).logicalSrcIdx = 37;
	  section.data(2).dtTransOffset = 4;
	
	  ;% q_2dsfl_pos_cntrl_P.Constant1_Value
	  section.data(3).logicalSrcIdx = 38;
	  section.data(3).dtTransOffset = 8;
	
	  ;% q_2dsfl_pos_cntrl_P.Cnstant2_Value
	  section.data(4).logicalSrcIdx = 39;
	  section.data(4).dtTransOffset = 12;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_OOTerminate
	  section.data(5).logicalSrcIdx = 40;
	  section.data(5).dtTransOffset = 16;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_OOExit
	  section.data(6).logicalSrcIdx = 41;
	  section.data(6).dtTransOffset = 17;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_OOStart
	  section.data(7).logicalSrcIdx = 42;
	  section.data(7).dtTransOffset = 18;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_OOEnter
	  section.data(8).logicalSrcIdx = 43;
	  section.data(8).dtTransOffset = 19;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_AOFinal
	  section.data(9).logicalSrcIdx = 44;
	  section.data(9).dtTransOffset = 20;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_POFinal
	  section.data(10).logicalSrcIdx = 45;
	  section.data(10).dtTransOffset = 21;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_AIHigh
	  section.data(11).logicalSrcIdx = 46;
	  section.data(11).dtTransOffset = 22;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_AILow
	  section.data(12).logicalSrcIdx = 47;
	  section.data(12).dtTransOffset = 23;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_AOHigh
	  section.data(13).logicalSrcIdx = 48;
	  section.data(13).dtTransOffset = 24;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_AOLow
	  section.data(14).logicalSrcIdx = 49;
	  section.data(14).dtTransOffset = 25;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_AOInitial
	  section.data(15).logicalSrcIdx = 50;
	  section.data(15).dtTransOffset = 26;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_AOWatchdog
	  section.data(16).logicalSrcIdx = 51;
	  section.data(16).dtTransOffset = 27;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_POFrequency
	  section.data(17).logicalSrcIdx = 52;
	  section.data(17).dtTransOffset = 28;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_POLeading
	  section.data(18).logicalSrcIdx = 53;
	  section.data(18).dtTransOffset = 29;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_POTrailing
	  section.data(19).logicalSrcIdx = 54;
	  section.data(19).dtTransOffset = 30;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_POInitial
	  section.data(20).logicalSrcIdx = 55;
	  section.data(20).dtTransOffset = 31;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_POWatchdog
	  section.data(21).logicalSrcIdx = 56;
	  section.data(21).dtTransOffset = 32;
	
	  ;% q_2dsfl_pos_cntrl_P.ContinuousSigmoid_XI
	  section.data(22).logicalSrcIdx = 57;
	  section.data(22).dtTransOffset = 33;
	
	  ;% q_2dsfl_pos_cntrl_P.ContinuousSigmoid_VI
	  section.data(23).logicalSrcIdx = 58;
	  section.data(23).dtTransOffset = 34;
	
	  ;% q_2dsfl_pos_cntrl_P.ContinuousSigmoid_Hold
	  section.data(24).logicalSrcIdx = 59;
	  section.data(24).dtTransOffset = 35;
	
	  ;% q_2dsfl_pos_cntrl_P.ContinuousSigmoid_VMax
	  section.data(25).logicalSrcIdx = 60;
	  section.data(25).dtTransOffset = 36;
	
	  ;% q_2dsfl_pos_cntrl_P.ContinuousSigmoid_AMax
	  section.data(26).logicalSrcIdx = 61;
	  section.data(26).dtTransOffset = 37;
	
	  ;% q_2dsfl_pos_cntrl_P.u100_Gain
	  section.data(27).logicalSrcIdx = 62;
	  section.data(27).dtTransOffset = 38;
	
	  ;% q_2dsfl_pos_cntrl_P.Filter3_A
	  section.data(28).logicalSrcIdx = 63;
	  section.data(28).dtTransOffset = 42;
	
	  ;% q_2dsfl_pos_cntrl_P.Filter3_C
	  section.data(29).logicalSrcIdx = 64;
	  section.data(29).dtTransOffset = 44;
	
	  ;% q_2dsfl_pos_cntrl_P.DerivativeFilter1_A
	  section.data(30).logicalSrcIdx = 65;
	  section.data(30).dtTransOffset = 46;
	
	  ;% q_2dsfl_pos_cntrl_P.DerivativeFilter1_C
	  section.data(31).logicalSrcIdx = 66;
	  section.data(31).dtTransOffset = 48;
	
	  ;% q_2dsfl_pos_cntrl_P.DerivativeFilter2_A
	  section.data(32).logicalSrcIdx = 67;
	  section.data(32).dtTransOffset = 50;
	
	  ;% q_2dsfl_pos_cntrl_P.DerivativeFilter2_C
	  section.data(33).logicalSrcIdx = 68;
	  section.data(33).dtTransOffset = 52;
	
	  ;% q_2dsfl_pos_cntrl_P.Gain_Gain
	  section.data(34).logicalSrcIdx = 69;
	  section.data(34).dtTransOffset = 54;
	
	  ;% q_2dsfl_pos_cntrl_P.Gain_Gain_o
	  section.data(35).logicalSrcIdx = 70;
	  section.data(35).dtTransOffset = 55;
	
	  ;% q_2dsfl_pos_cntrl_P.Im_r1Saturation_UpperSat
	  section.data(36).logicalSrcIdx = 71;
	  section.data(36).dtTransOffset = 56;
	
	  ;% q_2dsfl_pos_cntrl_P.Im_r1Saturation_LowerSat
	  section.data(37).logicalSrcIdx = 72;
	  section.data(37).dtTransOffset = 57;
	
	  ;% q_2dsfl_pos_cntrl_P.VoltstoAmps_Gain
	  section.data(38).logicalSrcIdx = 73;
	  section.data(38).dtTransOffset = 58;
	
	  ;% q_2dsfl_pos_cntrl_P.AmpstoVolts_Gain
	  section.data(39).logicalSrcIdx = 74;
	  section.data(39).dtTransOffset = 59;
	
	  ;% q_2dsfl_pos_cntrl_P.Gain_Gain_e
	  section.data(40).logicalSrcIdx = 75;
	  section.data(40).dtTransOffset = 60;
	
	  ;% q_2dsfl_pos_cntrl_P.TransportDelay_Delay
	  section.data(41).logicalSrcIdx = 76;
	  section.data(41).dtTransOffset = 61;
	
	  ;% q_2dsfl_pos_cntrl_P.TransportDelay_InitOutput
	  section.data(42).logicalSrcIdx = 77;
	  section.data(42).dtTransOffset = 62;
	
	  ;% q_2dsfl_pos_cntrl_P.u1001_Gain
	  section.data(43).logicalSrcIdx = 78;
	  section.data(43).dtTransOffset = 63;
	
	  ;% q_2dsfl_pos_cntrl_P.DerivativeFilter3_A
	  section.data(44).logicalSrcIdx = 79;
	  section.data(44).dtTransOffset = 67;
	
	  ;% q_2dsfl_pos_cntrl_P.DerivativeFilter3_C
	  section.data(45).logicalSrcIdx = 80;
	  section.data(45).dtTransOffset = 69;
	
	  ;% q_2dsfl_pos_cntrl_P.DerivativeFilter1_A_c
	  section.data(46).logicalSrcIdx = 81;
	  section.data(46).dtTransOffset = 71;
	
	  ;% q_2dsfl_pos_cntrl_P.DerivativeFilter1_C_l
	  section.data(47).logicalSrcIdx = 82;
	  section.data(47).dtTransOffset = 73;
	
	  ;% q_2dsfl_pos_cntrl_P.DerivativeFilter2_A_m
	  section.data(48).logicalSrcIdx = 83;
	  section.data(48).dtTransOffset = 75;
	
	  ;% q_2dsfl_pos_cntrl_P.DerivativeFilter2_C_g
	  section.data(49).logicalSrcIdx = 84;
	  section.data(49).dtTransOffset = 77;
	
	  ;% q_2dsfl_pos_cntrl_P.Gain_Gain_g
	  section.data(50).logicalSrcIdx = 85;
	  section.data(50).dtTransOffset = 79;
	
	  ;% q_2dsfl_pos_cntrl_P.Gain_Gain_k
	  section.data(51).logicalSrcIdx = 86;
	  section.data(51).dtTransOffset = 80;
	
	  ;% q_2dsfl_pos_cntrl_P.Im_r2Saturation_UpperSat
	  section.data(52).logicalSrcIdx = 87;
	  section.data(52).dtTransOffset = 81;
	
	  ;% q_2dsfl_pos_cntrl_P.Im_r2Saturation_LowerSat
	  section.data(53).logicalSrcIdx = 88;
	  section.data(53).dtTransOffset = 82;
	
	  ;% q_2dsfl_pos_cntrl_P.VoltstoAmps_Gain_p
	  section.data(54).logicalSrcIdx = 89;
	  section.data(54).dtTransOffset = 83;
	
	  ;% q_2dsfl_pos_cntrl_P.AmpstoVolts_Gain_j
	  section.data(55).logicalSrcIdx = 90;
	  section.data(55).dtTransOffset = 84;
	
	  ;% q_2dsfl_pos_cntrl_P.Gain_Gain_n
	  section.data(56).logicalSrcIdx = 91;
	  section.data(56).dtTransOffset = 85;
	
	  ;% q_2dsfl_pos_cntrl_P.SquareWave1_Amplitude
	  section.data(57).logicalSrcIdx = 92;
	  section.data(57).dtTransOffset = 86;
	
	  ;% q_2dsfl_pos_cntrl_P.SquareWave1_Frequency
	  section.data(58).logicalSrcIdx = 93;
	  section.data(58).dtTransOffset = 87;
	
	  ;% q_2dsfl_pos_cntrl_P.Amplitudedeg1_Gain
	  section.data(59).logicalSrcIdx = 94;
	  section.data(59).dtTransOffset = 88;
	
	  ;% q_2dsfl_pos_cntrl_P.ContinuousSigmoid1_XI
	  section.data(60).logicalSrcIdx = 95;
	  section.data(60).dtTransOffset = 89;
	
	  ;% q_2dsfl_pos_cntrl_P.ContinuousSigmoid1_VI
	  section.data(61).logicalSrcIdx = 96;
	  section.data(61).dtTransOffset = 90;
	
	  ;% q_2dsfl_pos_cntrl_P.ContinuousSigmoid1_Hold
	  section.data(62).logicalSrcIdx = 97;
	  section.data(62).dtTransOffset = 91;
	
	  ;% q_2dsfl_pos_cntrl_P.ContinuousSigmoid1_VMax
	  section.data(63).logicalSrcIdx = 98;
	  section.data(63).dtTransOffset = 92;
	
	  ;% q_2dsfl_pos_cntrl_P.ContinuousSigmoid1_AMax
	  section.data(64).logicalSrcIdx = 99;
	  section.data(64).dtTransOffset = 93;
	
	  ;% q_2dsfl_pos_cntrl_P.Gain1_Gain
	  section.data(65).logicalSrcIdx = 100;
	  section.data(65).dtTransOffset = 94;
	
	  ;% q_2dsfl_pos_cntrl_P.EnableActiveLow_Value
	  section.data(66).logicalSrcIdx = 101;
	  section.data(66).dtTransOffset = 95;
	
	  ;% q_2dsfl_pos_cntrl_P.MasterEnableActiveHigh_Value
	  section.data(67).logicalSrcIdx = 102;
	  section.data(67).dtTransOffset = 97;
	
	  ;% q_2dsfl_pos_cntrl_P.Amplitudedeg_Gain
	  section.data(68).logicalSrcIdx = 103;
	  section.data(68).dtTransOffset = 98;
	
	  ;% q_2dsfl_pos_cntrl_P.Gain1_Gain_j
	  section.data(69).logicalSrcIdx = 104;
	  section.data(69).dtTransOffset = 99;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(5) = section;
      clear section
      
      section.nData     = 8;
      section.data(8)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_CKChannels
	  section.data(1).logicalSrcIdx = 105;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_DOWatchdog
	  section.data(2).logicalSrcIdx = 106;
	  section.data(2).dtTransOffset = 3;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_EIInitial
	  section.data(3).logicalSrcIdx = 107;
	  section.data(3).dtTransOffset = 4;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_POModes
	  section.data(4).logicalSrcIdx = 108;
	  section.data(4).dtTransOffset = 5;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_POConfiguration
	  section.data(5).logicalSrcIdx = 109;
	  section.data(5).dtTransOffset = 6;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_POAlignment
	  section.data(6).logicalSrcIdx = 110;
	  section.data(6).dtTransOffset = 7;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_POPolarity
	  section.data(7).logicalSrcIdx = 111;
	  section.data(7).dtTransOffset = 8;
	
	  ;% q_2dsfl_pos_cntrl_P.HILReadEncoderTimebase_Clock
	  section.data(8).logicalSrcIdx = 112;
	  section.data(8).dtTransOffset = 9;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(6) = section;
      clear section
      
      section.nData     = 7;
      section.data(7)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_AIChannels
	  section.data(1).logicalSrcIdx = 113;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_AOChannels
	  section.data(2).logicalSrcIdx = 114;
	  section.data(2).dtTransOffset = 8;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_EIChannels
	  section.data(3).logicalSrcIdx = 115;
	  section.data(3).dtTransOffset = 16;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_EIQuadrature
	  section.data(4).logicalSrcIdx = 116;
	  section.data(4).dtTransOffset = 24;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_POChannels
	  section.data(5).logicalSrcIdx = 117;
	  section.data(5).dtTransOffset = 25;
	
	  ;% q_2dsfl_pos_cntrl_P.HILReadEncoderTimebase_Channels
	  section.data(6).logicalSrcIdx = 118;
	  section.data(6).dtTransOffset = 33;
	
	  ;% q_2dsfl_pos_cntrl_P.HILReadEncoderTimebase_SamplesI
	  section.data(7).logicalSrcIdx = 119;
	  section.data(7).dtTransOffset = 34;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(7) = section;
      clear section
      
      section.nData     = 51;
      section.data(51)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_P.Constant_Value
	  section.data(1).logicalSrcIdx = 120;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_pos_cntrl_P.Constant_Value_a
	  section.data(2).logicalSrcIdx = 121;
	  section.data(2).dtTransOffset = 1;
	
	  ;% q_2dsfl_pos_cntrl_P.Constant_Value_p
	  section.data(3).logicalSrcIdx = 122;
	  section.data(3).dtTransOffset = 2;
	
	  ;% q_2dsfl_pos_cntrl_P.Constant_Value_f
	  section.data(4).logicalSrcIdx = 123;
	  section.data(4).dtTransOffset = 3;
	
	  ;% q_2dsfl_pos_cntrl_P.Constant_Value_g
	  section.data(5).logicalSrcIdx = 124;
	  section.data(5).dtTransOffset = 4;
	
	  ;% q_2dsfl_pos_cntrl_P.Constant_Value_fj
	  section.data(6).logicalSrcIdx = 125;
	  section.data(6).dtTransOffset = 5;
	
	  ;% q_2dsfl_pos_cntrl_P.Constant_Value_k
	  section.data(7).logicalSrcIdx = 126;
	  section.data(7).dtTransOffset = 6;
	
	  ;% q_2dsfl_pos_cntrl_P.Constant_Value_ks
	  section.data(8).logicalSrcIdx = 127;
	  section.data(8).dtTransOffset = 7;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_Active
	  section.data(9).logicalSrcIdx = 128;
	  section.data(9).dtTransOffset = 8;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_AOTerminate
	  section.data(10).logicalSrcIdx = 129;
	  section.data(10).dtTransOffset = 9;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_AOExit
	  section.data(11).logicalSrcIdx = 130;
	  section.data(11).dtTransOffset = 10;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_DOTerminate
	  section.data(12).logicalSrcIdx = 131;
	  section.data(12).dtTransOffset = 11;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_DOExit
	  section.data(13).logicalSrcIdx = 132;
	  section.data(13).dtTransOffset = 12;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_POTerminate
	  section.data(14).logicalSrcIdx = 133;
	  section.data(14).dtTransOffset = 13;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_POExit
	  section.data(15).logicalSrcIdx = 134;
	  section.data(15).dtTransOffset = 14;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_CKPStart
	  section.data(16).logicalSrcIdx = 135;
	  section.data(16).dtTransOffset = 15;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_CKPEnter
	  section.data(17).logicalSrcIdx = 136;
	  section.data(17).dtTransOffset = 16;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_CKStart
	  section.data(18).logicalSrcIdx = 137;
	  section.data(18).dtTransOffset = 17;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_CKEnter
	  section.data(19).logicalSrcIdx = 138;
	  section.data(19).dtTransOffset = 18;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_AIPStart
	  section.data(20).logicalSrcIdx = 139;
	  section.data(20).dtTransOffset = 19;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_AIPEnter
	  section.data(21).logicalSrcIdx = 140;
	  section.data(21).dtTransOffset = 20;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_AOPStart
	  section.data(22).logicalSrcIdx = 141;
	  section.data(22).dtTransOffset = 21;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_AOPEnter
	  section.data(23).logicalSrcIdx = 142;
	  section.data(23).dtTransOffset = 22;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_AOStart
	  section.data(24).logicalSrcIdx = 143;
	  section.data(24).dtTransOffset = 23;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_AOEnter
	  section.data(25).logicalSrcIdx = 144;
	  section.data(25).dtTransOffset = 24;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_AOReset
	  section.data(26).logicalSrcIdx = 145;
	  section.data(26).dtTransOffset = 25;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_DOPStart
	  section.data(27).logicalSrcIdx = 146;
	  section.data(27).dtTransOffset = 26;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_DOPEnter
	  section.data(28).logicalSrcIdx = 147;
	  section.data(28).dtTransOffset = 27;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_DOStart
	  section.data(29).logicalSrcIdx = 148;
	  section.data(29).dtTransOffset = 28;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_DOEnter
	  section.data(30).logicalSrcIdx = 149;
	  section.data(30).dtTransOffset = 29;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_DOReset
	  section.data(31).logicalSrcIdx = 150;
	  section.data(31).dtTransOffset = 30;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_EIPStart
	  section.data(32).logicalSrcIdx = 151;
	  section.data(32).dtTransOffset = 31;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_EIPEnter
	  section.data(33).logicalSrcIdx = 152;
	  section.data(33).dtTransOffset = 32;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_EIStart
	  section.data(34).logicalSrcIdx = 153;
	  section.data(34).dtTransOffset = 33;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_EIEnter
	  section.data(35).logicalSrcIdx = 154;
	  section.data(35).dtTransOffset = 34;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_POPStart
	  section.data(36).logicalSrcIdx = 155;
	  section.data(36).dtTransOffset = 35;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_POPEnter
	  section.data(37).logicalSrcIdx = 156;
	  section.data(37).dtTransOffset = 36;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_POStart
	  section.data(38).logicalSrcIdx = 157;
	  section.data(38).dtTransOffset = 37;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_POEnter
	  section.data(39).logicalSrcIdx = 158;
	  section.data(39).dtTransOffset = 38;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_POReset
	  section.data(40).logicalSrcIdx = 159;
	  section.data(40).dtTransOffset = 39;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_OOReset
	  section.data(41).logicalSrcIdx = 160;
	  section.data(41).dtTransOffset = 40;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_DOFinal
	  section.data(42).logicalSrcIdx = 161;
	  section.data(42).dtTransOffset = 41;
	
	  ;% q_2dsfl_pos_cntrl_P.HILInitialize_DOInitial
	  section.data(43).logicalSrcIdx = 162;
	  section.data(43).dtTransOffset = 42;
	
	  ;% q_2dsfl_pos_cntrl_P.HILReadEncoderTimebase_Active
	  section.data(44).logicalSrcIdx = 163;
	  section.data(44).dtTransOffset = 43;
	
	  ;% q_2dsfl_pos_cntrl_P.HILReadAnalog_Active
	  section.data(45).logicalSrcIdx = 164;
	  section.data(45).dtTransOffset = 44;
	
	  ;% q_2dsfl_pos_cntrl_P.HILWriteAnalog_Active
	  section.data(46).logicalSrcIdx = 165;
	  section.data(46).dtTransOffset = 45;
	
	  ;% q_2dsfl_pos_cntrl_P.HILReadEncoder_Active
	  section.data(47).logicalSrcIdx = 166;
	  section.data(47).dtTransOffset = 46;
	
	  ;% q_2dsfl_pos_cntrl_P.HILReadAnalog_Active_i
	  section.data(48).logicalSrcIdx = 167;
	  section.data(48).dtTransOffset = 47;
	
	  ;% q_2dsfl_pos_cntrl_P.HILWriteAnalog_Active_f
	  section.data(49).logicalSrcIdx = 168;
	  section.data(49).dtTransOffset = 48;
	
	  ;% q_2dsfl_pos_cntrl_P.HILWriteDigital_Active
	  section.data(50).logicalSrcIdx = 169;
	  section.data(50).dtTransOffset = 49;
	
	  ;% q_2dsfl_pos_cntrl_P.HILReadDigital_Active
	  section.data(51).logicalSrcIdx = 170;
	  section.data(51).dtTransOffset = 50;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(8) = section;
      clear section
      
      section.nData     = 6;
      section.data(6)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_P.Constant_Value_d
	  section.data(1).logicalSrcIdx = 171;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_pos_cntrl_P.HILReadEncoderTimebase_Overflow
	  section.data(2).logicalSrcIdx = 172;
	  section.data(2).dtTransOffset = 1;
	
	  ;% q_2dsfl_pos_cntrl_P.ManualSwitch1_CurrentSetting
	  section.data(3).logicalSrcIdx = 173;
	  section.data(3).dtTransOffset = 2;
	
	  ;% q_2dsfl_pos_cntrl_P.ManualSwitch2_CurrentSetting
	  section.data(4).logicalSrcIdx = 174;
	  section.data(4).dtTransOffset = 3;
	
	  ;% q_2dsfl_pos_cntrl_P.Output_InitialCondition
	  section.data(5).logicalSrcIdx = 175;
	  section.data(5).dtTransOffset = 4;
	
	  ;% q_2dsfl_pos_cntrl_P.FixPtConstant_Value
	  section.data(6).logicalSrcIdx = 176;
	  section.data(6).dtTransOffset = 5;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(9) = section;
      clear section
      
      section.nData     = 11;
      section.data(11)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_P.BiasRemoval_m.unity_Value
	  section.data(1).logicalSrcIdx = 177;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_pos_cntrl_P.BiasRemoval_m.UnitDelay_InitialCondition
	  section.data(2).logicalSrcIdx = 178;
	  section.data(2).dtTransOffset = 1;
	
	  ;% q_2dsfl_pos_cntrl_P.BiasRemoval_m.Sumk1n1xk_InitialCondition
	  section.data(3).logicalSrcIdx = 179;
	  section.data(3).dtTransOffset = 2;
	
	  ;% q_2dsfl_pos_cntrl_P.BiasRemoval_m.zero_Y0
	  section.data(4).logicalSrcIdx = 180;
	  section.data(4).dtTransOffset = 3;
	
	  ;% q_2dsfl_pos_cntrl_P.BiasRemoval_m.Constant_Value
	  section.data(5).logicalSrcIdx = 181;
	  section.data(5).dtTransOffset = 4;
	
	  ;% q_2dsfl_pos_cntrl_P.BiasRemoval_m.Vbiased_Y0
	  section.data(6).logicalSrcIdx = 182;
	  section.data(6).dtTransOffset = 5;
	
	  ;% q_2dsfl_pos_cntrl_P.BiasRemoval_m.Vunbiased_Y0
	  section.data(7).logicalSrcIdx = 183;
	  section.data(7).dtTransOffset = 6;
	
	  ;% q_2dsfl_pos_cntrl_P.BiasRemoval_m.Stepstart_time_Y0
	  section.data(8).logicalSrcIdx = 184;
	  section.data(8).dtTransOffset = 7;
	
	  ;% q_2dsfl_pos_cntrl_P.BiasRemoval_m.Stepstart_time_YFinal
	  section.data(9).logicalSrcIdx = 185;
	  section.data(9).dtTransOffset = 8;
	
	  ;% q_2dsfl_pos_cntrl_P.BiasRemoval_m.Stepend_time_Y0
	  section.data(10).logicalSrcIdx = 186;
	  section.data(10).dtTransOffset = 9;
	
	  ;% q_2dsfl_pos_cntrl_P.BiasRemoval_m.Stepend_time_YFinal
	  section.data(11).logicalSrcIdx = 187;
	  section.data(11).dtTransOffset = 10;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(10) = section;
      clear section
      
      section.nData     = 11;
      section.data(11)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_P.BiasRemoval.unity_Value
	  section.data(1).logicalSrcIdx = 188;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_pos_cntrl_P.BiasRemoval.UnitDelay_InitialCondition
	  section.data(2).logicalSrcIdx = 189;
	  section.data(2).dtTransOffset = 1;
	
	  ;% q_2dsfl_pos_cntrl_P.BiasRemoval.Sumk1n1xk_InitialCondition
	  section.data(3).logicalSrcIdx = 190;
	  section.data(3).dtTransOffset = 2;
	
	  ;% q_2dsfl_pos_cntrl_P.BiasRemoval.zero_Y0
	  section.data(4).logicalSrcIdx = 191;
	  section.data(4).dtTransOffset = 3;
	
	  ;% q_2dsfl_pos_cntrl_P.BiasRemoval.Constant_Value
	  section.data(5).logicalSrcIdx = 192;
	  section.data(5).dtTransOffset = 4;
	
	  ;% q_2dsfl_pos_cntrl_P.BiasRemoval.Vbiased_Y0
	  section.data(6).logicalSrcIdx = 193;
	  section.data(6).dtTransOffset = 5;
	
	  ;% q_2dsfl_pos_cntrl_P.BiasRemoval.Vunbiased_Y0
	  section.data(7).logicalSrcIdx = 194;
	  section.data(7).dtTransOffset = 6;
	
	  ;% q_2dsfl_pos_cntrl_P.BiasRemoval.Stepstart_time_Y0
	  section.data(8).logicalSrcIdx = 195;
	  section.data(8).dtTransOffset = 7;
	
	  ;% q_2dsfl_pos_cntrl_P.BiasRemoval.Stepstart_time_YFinal
	  section.data(9).logicalSrcIdx = 196;
	  section.data(9).dtTransOffset = 8;
	
	  ;% q_2dsfl_pos_cntrl_P.BiasRemoval.Stepend_time_Y0
	  section.data(10).logicalSrcIdx = 197;
	  section.data(10).dtTransOffset = 9;
	
	  ;% q_2dsfl_pos_cntrl_P.BiasRemoval.Stepend_time_YFinal
	  section.data(11).logicalSrcIdx = 198;
	  section.data(11).dtTransOffset = 10;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(11) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (parameter)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    paramMap.nTotData = nTotData;
    


  ;%**************************
  ;% Create Block Output Map *
  ;%**************************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 5;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc sigMap
    ;%
    sigMap.nSections           = nTotSects;
    sigMap.sectIdxOffset       = sectIdxOffset;
      sigMap.sections(nTotSects) = dumSection; %prealloc
    sigMap.nTotData            = -1;
    
    ;%
    ;% Auto data (q_2dsfl_pos_cntrl_B)
    ;%
      section.nData     = 37;
      section.data(37)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_B.ContinuousSigmoid_o1
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_pos_cntrl_B.ContinuousSigmoid_o2
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% q_2dsfl_pos_cntrl_B.ContinuousSigmoid_o3
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% q_2dsfl_pos_cntrl_B.ContinuousSigmoid_o4
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% q_2dsfl_pos_cntrl_B.u100
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% q_2dsfl_pos_cntrl_B.Motor1EncoderCalib
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 8;
	
	  ;% q_2dsfl_pos_cntrl_B.Filter3
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 9;
	
	  ;% q_2dsfl_pos_cntrl_B.DerivativeFilter1
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 10;
	
	  ;% q_2dsfl_pos_cntrl_B.DerivativeFilter2
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 11;
	
	  ;% q_2dsfl_pos_cntrl_B.Gain
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 12;
	
	  ;% q_2dsfl_pos_cntrl_B.Gain_n
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 14;
	
	  ;% q_2dsfl_pos_cntrl_B.ManualSwitch1
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 16;
	
	  ;% q_2dsfl_pos_cntrl_B.Im_r1Saturation
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 20;
	
	  ;% q_2dsfl_pos_cntrl_B.VoltstoAmps
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 21;
	
	  ;% q_2dsfl_pos_cntrl_B.AmpstoVolts
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 22;
	
	  ;% q_2dsfl_pos_cntrl_B.positiveCCW
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 23;
	
	  ;% q_2dsfl_pos_cntrl_B.StraintoDeflection
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 24;
	
	  ;% q_2dsfl_pos_cntrl_B.u1001
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 25;
	
	  ;% q_2dsfl_pos_cntrl_B.Motor2EncoderCalib
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 29;
	
	  ;% q_2dsfl_pos_cntrl_B.DerivativeFilter3
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 30;
	
	  ;% q_2dsfl_pos_cntrl_B.DerivativeFilter1_l
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 31;
	
	  ;% q_2dsfl_pos_cntrl_B.DerivativeFilter2_e
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 32;
	
	  ;% q_2dsfl_pos_cntrl_B.Gain_m
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 33;
	
	  ;% q_2dsfl_pos_cntrl_B.Gain_b
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 35;
	
	  ;% q_2dsfl_pos_cntrl_B.positiveCCW_h
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 37;
	
	  ;% q_2dsfl_pos_cntrl_B.VoltstoStrain
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 38;
	
	  ;% q_2dsfl_pos_cntrl_B.ManualSwitch2
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 39;
	
	  ;% q_2dsfl_pos_cntrl_B.Im_r2Saturation
	  section.data(28).logicalSrcIdx = 27;
	  section.data(28).dtTransOffset = 43;
	
	  ;% q_2dsfl_pos_cntrl_B.VoltstoAmps_i
	  section.data(29).logicalSrcIdx = 28;
	  section.data(29).dtTransOffset = 44;
	
	  ;% q_2dsfl_pos_cntrl_B.AmpstoVolts_g
	  section.data(30).logicalSrcIdx = 29;
	  section.data(30).dtTransOffset = 45;
	
	  ;% q_2dsfl_pos_cntrl_B.StraintoDeflection_i
	  section.data(31).logicalSrcIdx = 30;
	  section.data(31).dtTransOffset = 46;
	
	  ;% q_2dsfl_pos_cntrl_B.ContinuousSigmoid1_o1
	  section.data(32).logicalSrcIdx = 31;
	  section.data(32).dtTransOffset = 47;
	
	  ;% q_2dsfl_pos_cntrl_B.ContinuousSigmoid1_o2
	  section.data(33).logicalSrcIdx = 32;
	  section.data(33).dtTransOffset = 48;
	
	  ;% q_2dsfl_pos_cntrl_B.ContinuousSigmoid1_o3
	  section.data(34).logicalSrcIdx = 33;
	  section.data(34).dtTransOffset = 49;
	
	  ;% q_2dsfl_pos_cntrl_B.ContinuousSigmoid1_o4
	  section.data(35).logicalSrcIdx = 34;
	  section.data(35).dtTransOffset = 50;
	
	  ;% q_2dsfl_pos_cntrl_B.Gain1
	  section.data(36).logicalSrcIdx = 35;
	  section.data(36).dtTransOffset = 51;
	
	  ;% q_2dsfl_pos_cntrl_B.Gain1_e
	  section.data(37).logicalSrcIdx = 36;
	  section.data(37).dtTransOffset = 52;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_B.FixPtSwitch
	  section.data(1).logicalSrcIdx = 37;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(2) = section;
      clear section
      
      section.nData     = 12;
      section.data(12)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_B.LogicalOperator4
	  section.data(1).logicalSrcIdx = 38;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_pos_cntrl_B.LogicalOperator5
	  section.data(2).logicalSrcIdx = 39;
	  section.data(2).dtTransOffset = 1;
	
	  ;% q_2dsfl_pos_cntrl_B.LogicalOperator6
	  section.data(3).logicalSrcIdx = 40;
	  section.data(3).dtTransOffset = 2;
	
	  ;% q_2dsfl_pos_cntrl_B.LogicalOperator7
	  section.data(4).logicalSrcIdx = 41;
	  section.data(4).dtTransOffset = 3;
	
	  ;% q_2dsfl_pos_cntrl_B.CheckMaximumAllowedPosition
	  section.data(5).logicalSrcIdx = 42;
	  section.data(5).dtTransOffset = 4;
	
	  ;% q_2dsfl_pos_cntrl_B.Compare
	  section.data(6).logicalSrcIdx = 43;
	  section.data(6).dtTransOffset = 5;
	
	  ;% q_2dsfl_pos_cntrl_B.CheckMinimumAllowedPosition
	  section.data(7).logicalSrcIdx = 44;
	  section.data(7).dtTransOffset = 6;
	
	  ;% q_2dsfl_pos_cntrl_B.Compare_j
	  section.data(8).logicalSrcIdx = 45;
	  section.data(8).dtTransOffset = 7;
	
	  ;% q_2dsfl_pos_cntrl_B.CheckMaximumAllowedPosition_c
	  section.data(9).logicalSrcIdx = 46;
	  section.data(9).dtTransOffset = 8;
	
	  ;% q_2dsfl_pos_cntrl_B.Compare_c
	  section.data(10).logicalSrcIdx = 47;
	  section.data(10).dtTransOffset = 9;
	
	  ;% q_2dsfl_pos_cntrl_B.CheckMinimumAllowedPosition_a
	  section.data(11).logicalSrcIdx = 48;
	  section.data(11).dtTransOffset = 10;
	
	  ;% q_2dsfl_pos_cntrl_B.Compare_e
	  section.data(12).logicalSrcIdx = 49;
	  section.data(12).dtTransOffset = 11;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(3) = section;
      clear section
      
      section.nData     = 7;
      section.data(7)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_B.BiasRemoval_m.Switch
	  section.data(1).logicalSrcIdx = 50;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_pos_cntrl_B.BiasRemoval_m.VVavg
	  section.data(2).logicalSrcIdx = 51;
	  section.data(2).dtTransOffset = 1;
	
	  ;% q_2dsfl_pos_cntrl_B.BiasRemoval_m.Vin
	  section.data(3).logicalSrcIdx = 52;
	  section.data(3).dtTransOffset = 2;
	
	  ;% q_2dsfl_pos_cntrl_B.BiasRemoval_m.Constant
	  section.data(4).logicalSrcIdx = 53;
	  section.data(4).dtTransOffset = 3;
	
	  ;% q_2dsfl_pos_cntrl_B.BiasRemoval_m.Count
	  section.data(5).logicalSrcIdx = 54;
	  section.data(5).dtTransOffset = 4;
	
	  ;% q_2dsfl_pos_cntrl_B.BiasRemoval_m.Sum
	  section.data(6).logicalSrcIdx = 55;
	  section.data(6).dtTransOffset = 5;
	
	  ;% q_2dsfl_pos_cntrl_B.BiasRemoval_m.div
	  section.data(7).logicalSrcIdx = 56;
	  section.data(7).dtTransOffset = 6;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(4) = section;
      clear section
      
      section.nData     = 7;
      section.data(7)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_B.BiasRemoval.Switch
	  section.data(1).logicalSrcIdx = 58;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_pos_cntrl_B.BiasRemoval.VVavg
	  section.data(2).logicalSrcIdx = 59;
	  section.data(2).dtTransOffset = 1;
	
	  ;% q_2dsfl_pos_cntrl_B.BiasRemoval.Vin
	  section.data(3).logicalSrcIdx = 60;
	  section.data(3).dtTransOffset = 2;
	
	  ;% q_2dsfl_pos_cntrl_B.BiasRemoval.Constant
	  section.data(4).logicalSrcIdx = 61;
	  section.data(4).dtTransOffset = 3;
	
	  ;% q_2dsfl_pos_cntrl_B.BiasRemoval.Count
	  section.data(5).logicalSrcIdx = 62;
	  section.data(5).dtTransOffset = 4;
	
	  ;% q_2dsfl_pos_cntrl_B.BiasRemoval.Sum
	  section.data(6).logicalSrcIdx = 63;
	  section.data(6).dtTransOffset = 5;
	
	  ;% q_2dsfl_pos_cntrl_B.BiasRemoval.div
	  section.data(7).logicalSrcIdx = 64;
	  section.data(7).dtTransOffset = 6;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(5) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (signal)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    sigMap.nTotData = nTotData;
    


  ;%*******************
  ;% Create DWork Map *
  ;%*******************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 19;
    sectIdxOffset = 5;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc dworkMap
    ;%
    dworkMap.nSections           = nTotSects;
    dworkMap.sectIdxOffset       = sectIdxOffset;
      dworkMap.sections(nTotSects) = dumSection; %prealloc
    dworkMap.nTotData            = -1;
    
    ;%
    ;% Auto data (q_2dsfl_pos_cntrl_DW)
    ;%
      section.nData     = 12;
      section.data(12)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_DW.HILInitialize_AIMinimums
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_pos_cntrl_DW.HILInitialize_AIMaximums
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 8;
	
	  ;% q_2dsfl_pos_cntrl_DW.HILInitialize_AOMinimums
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 16;
	
	  ;% q_2dsfl_pos_cntrl_DW.HILInitialize_AOMaximums
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 24;
	
	  ;% q_2dsfl_pos_cntrl_DW.HILInitialize_AOVoltages
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 32;
	
	  ;% q_2dsfl_pos_cntrl_DW.HILInitialize_FilterFrequency
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 40;
	
	  ;% q_2dsfl_pos_cntrl_DW.HILInitialize_POSortedFreqs
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 48;
	
	  ;% q_2dsfl_pos_cntrl_DW.HILInitialize_POValues
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 56;
	
	  ;% q_2dsfl_pos_cntrl_DW.ContinuousSigmoid_Sigmoid
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 64;
	
	  ;% q_2dsfl_pos_cntrl_DW.HILReadAnalog_Buffer
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 75;
	
	  ;% q_2dsfl_pos_cntrl_DW.HILReadAnalog_Buffer_p
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 77;
	
	  ;% q_2dsfl_pos_cntrl_DW.ContinuousSigmoid1_Sigmoid
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 79;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_DW.HILReadEncoderTimebase_Task
	  section.data(1).logicalSrcIdx = 12;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_DW.HILInitialize_Card
	  section.data(1).logicalSrcIdx = 13;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 3;
      section.data(3)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_DW.ContinuousSigmoid_RWORK.Time
	  section.data(1).logicalSrcIdx = 14;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_pos_cntrl_DW.TransportDelay_RWORK.modelTStart
	  section.data(2).logicalSrcIdx = 15;
	  section.data(2).dtTransOffset = 1;
	
	  ;% q_2dsfl_pos_cntrl_DW.ContinuousSigmoid1_RWORK.Time
	  section.data(3).logicalSrcIdx = 16;
	  section.data(3).dtTransOffset = 2;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 21;
      section.data(21)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_DW.Scope_PWORK.LoggedData
	  section.data(1).logicalSrcIdx = 17;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_pos_cntrl_DW.Scope1_PWORK.LoggedData
	  section.data(2).logicalSrcIdx = 18;
	  section.data(2).dtTransOffset = 1;
	
	  ;% q_2dsfl_pos_cntrl_DW.theta11deg_PWORK.LoggedData
	  section.data(3).logicalSrcIdx = 19;
	  section.data(3).dtTransOffset = 2;
	
	  ;% q_2dsfl_pos_cntrl_DW.theta12deg_PWORK.LoggedData
	  section.data(4).logicalSrcIdx = 20;
	  section.data(4).dtTransOffset = 3;
	
	  ;% q_2dsfl_pos_cntrl_DW.HILReadAnalog_PWORK
	  section.data(5).logicalSrcIdx = 21;
	  section.data(5).dtTransOffset = 4;
	
	  ;% q_2dsfl_pos_cntrl_DW.CurrentResponse1A_PWORK.LoggedData
	  section.data(6).logicalSrcIdx = 22;
	  section.data(6).dtTransOffset = 5;
	
	  ;% q_2dsfl_pos_cntrl_DW.HILWriteAnalog_PWORK
	  section.data(7).logicalSrcIdx = 23;
	  section.data(7).dtTransOffset = 6;
	
	  ;% q_2dsfl_pos_cntrl_DW.StrainGauge0V_PWORK.LoggedData
	  section.data(8).logicalSrcIdx = 24;
	  section.data(8).dtTransOffset = 7;
	
	  ;% q_2dsfl_pos_cntrl_DW.TransportDelay_PWORK.TUbufferPtrs
	  section.data(9).logicalSrcIdx = 25;
	  section.data(9).dtTransOffset = 8;
	
	  ;% q_2dsfl_pos_cntrl_DW.Scope2_PWORK.LoggedData
	  section.data(10).logicalSrcIdx = 26;
	  section.data(10).dtTransOffset = 10;
	
	  ;% q_2dsfl_pos_cntrl_DW.HILReadEncoder_PWORK
	  section.data(11).logicalSrcIdx = 27;
	  section.data(11).dtTransOffset = 11;
	
	  ;% q_2dsfl_pos_cntrl_DW.Scope3_PWORK.LoggedData
	  section.data(12).logicalSrcIdx = 28;
	  section.data(12).dtTransOffset = 12;
	
	  ;% q_2dsfl_pos_cntrl_DW.theta21deg_PWORK.LoggedData
	  section.data(13).logicalSrcIdx = 29;
	  section.data(13).dtTransOffset = 13;
	
	  ;% q_2dsfl_pos_cntrl_DW.theta22deg_PWORK.LoggedData
	  section.data(14).logicalSrcIdx = 30;
	  section.data(14).dtTransOffset = 14;
	
	  ;% q_2dsfl_pos_cntrl_DW.HILReadAnalog_PWORK_f
	  section.data(15).logicalSrcIdx = 31;
	  section.data(15).dtTransOffset = 15;
	
	  ;% q_2dsfl_pos_cntrl_DW.BaseStrainmmmm_PWORK.LoggedData
	  section.data(16).logicalSrcIdx = 32;
	  section.data(16).dtTransOffset = 16;
	
	  ;% q_2dsfl_pos_cntrl_DW.CurrentResponse2A_PWORK.LoggedData
	  section.data(17).logicalSrcIdx = 33;
	  section.data(17).dtTransOffset = 17;
	
	  ;% q_2dsfl_pos_cntrl_DW.HILWriteAnalog_PWORK_l
	  section.data(18).logicalSrcIdx = 34;
	  section.data(18).dtTransOffset = 18;
	
	  ;% q_2dsfl_pos_cntrl_DW.StrainGauge1V_PWORK.LoggedData
	  section.data(19).logicalSrcIdx = 35;
	  section.data(19).dtTransOffset = 19;
	
	  ;% q_2dsfl_pos_cntrl_DW.HILWriteDigital_PWORK
	  section.data(20).logicalSrcIdx = 36;
	  section.data(20).dtTransOffset = 20;
	
	  ;% q_2dsfl_pos_cntrl_DW.HILReadDigital_PWORK
	  section.data(21).logicalSrcIdx = 37;
	  section.data(21).dtTransOffset = 21;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
      clear section
      
      section.nData     = 8;
      section.data(8)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_DW.HILInitialize_ClockModes
	  section.data(1).logicalSrcIdx = 38;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_pos_cntrl_DW.HILInitialize_QuadratureModes
	  section.data(2).logicalSrcIdx = 39;
	  section.data(2).dtTransOffset = 3;
	
	  ;% q_2dsfl_pos_cntrl_DW.HILInitialize_InitialEICounts
	  section.data(3).logicalSrcIdx = 40;
	  section.data(3).dtTransOffset = 11;
	
	  ;% q_2dsfl_pos_cntrl_DW.HILInitialize_POModeValues
	  section.data(4).logicalSrcIdx = 41;
	  section.data(4).dtTransOffset = 19;
	
	  ;% q_2dsfl_pos_cntrl_DW.HILInitialize_POAlignValues
	  section.data(5).logicalSrcIdx = 42;
	  section.data(5).dtTransOffset = 27;
	
	  ;% q_2dsfl_pos_cntrl_DW.HILInitialize_POPolarityVals
	  section.data(6).logicalSrcIdx = 43;
	  section.data(6).dtTransOffset = 35;
	
	  ;% q_2dsfl_pos_cntrl_DW.HILReadEncoderTimebase_Buffer
	  section.data(7).logicalSrcIdx = 44;
	  section.data(7).dtTransOffset = 43;
	
	  ;% q_2dsfl_pos_cntrl_DW.HILReadEncoder_Buffer
	  section.data(8).logicalSrcIdx = 45;
	  section.data(8).dtTransOffset = 44;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(6) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_DW.HILInitialize_POSortedChans
	  section.data(1).logicalSrcIdx = 46;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(7) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_DW.TransportDelay_IWORK.Tail
	  section.data(1).logicalSrcIdx = 47;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(8) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_DW.Output_DSTATE
	  section.data(1).logicalSrcIdx = 48;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(9) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_DW.PositionWatchdog_SubsysRanBC
	  section.data(1).logicalSrcIdx = 49;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_pos_cntrl_DW.PositionWatchdog_SubsysRanBC_c
	  section.data(2).logicalSrcIdx = 50;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(10) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_DW.ContinuousSigmoid_Flag
	  section.data(1).logicalSrcIdx = 51;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_pos_cntrl_DW.ContinuousSigmoid1_Flag
	  section.data(2).logicalSrcIdx = 52;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(11) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_DW.HILWriteDigital_Buffer
	  section.data(1).logicalSrcIdx = 53;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_pos_cntrl_DW.HILReadDigital_Buffer
	  section.data(2).logicalSrcIdx = 54;
	  section.data(2).dtTransOffset = 3;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(12) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_DW.PositionWatchdog_MODE
	  section.data(1).logicalSrcIdx = 55;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_pos_cntrl_DW.PositionWatchdog_MODE_l
	  section.data(2).logicalSrcIdx = 56;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(13) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_DW.BiasRemoval_m.UnitDelay_DSTATE
	  section.data(1).logicalSrcIdx = 57;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_pos_cntrl_DW.BiasRemoval_m.Sumk1n1xk_DSTATE
	  section.data(2).logicalSrcIdx = 58;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(14) = section;
      clear section
      
      section.nData     = 5;
      section.data(5)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_DW.BiasRemoval_m.SwitchCase_ActiveSubsystem
	  section.data(1).logicalSrcIdx = 59;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_pos_cntrl_DW.BiasRemoval_m.SwitchCaseActionSubsystem2_Subs
	  section.data(2).logicalSrcIdx = 60;
	  section.data(2).dtTransOffset = 1;
	
	  ;% q_2dsfl_pos_cntrl_DW.BiasRemoval_m.SwitchCaseActionSubsystem1_Subs
	  section.data(3).logicalSrcIdx = 61;
	  section.data(3).dtTransOffset = 2;
	
	  ;% q_2dsfl_pos_cntrl_DW.BiasRemoval_m.SwitchCaseActionSubsystem_Subsy
	  section.data(4).logicalSrcIdx = 62;
	  section.data(4).dtTransOffset = 3;
	
	  ;% q_2dsfl_pos_cntrl_DW.BiasRemoval_m.EnabledMovingAverage_SubsysRanB
	  section.data(5).logicalSrcIdx = 63;
	  section.data(5).dtTransOffset = 4;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(15) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_DW.BiasRemoval_m.EnabledMovingAverage_MODE
	  section.data(1).logicalSrcIdx = 64;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(16) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_DW.BiasRemoval.UnitDelay_DSTATE
	  section.data(1).logicalSrcIdx = 65;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_pos_cntrl_DW.BiasRemoval.Sumk1n1xk_DSTATE
	  section.data(2).logicalSrcIdx = 66;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(17) = section;
      clear section
      
      section.nData     = 5;
      section.data(5)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_DW.BiasRemoval.SwitchCase_ActiveSubsystem
	  section.data(1).logicalSrcIdx = 67;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_2dsfl_pos_cntrl_DW.BiasRemoval.SwitchCaseActionSubsystem2_Subs
	  section.data(2).logicalSrcIdx = 68;
	  section.data(2).dtTransOffset = 1;
	
	  ;% q_2dsfl_pos_cntrl_DW.BiasRemoval.SwitchCaseActionSubsystem1_Subs
	  section.data(3).logicalSrcIdx = 69;
	  section.data(3).dtTransOffset = 2;
	
	  ;% q_2dsfl_pos_cntrl_DW.BiasRemoval.SwitchCaseActionSubsystem_Subsy
	  section.data(4).logicalSrcIdx = 70;
	  section.data(4).dtTransOffset = 3;
	
	  ;% q_2dsfl_pos_cntrl_DW.BiasRemoval.EnabledMovingAverage_SubsysRanB
	  section.data(5).logicalSrcIdx = 71;
	  section.data(5).dtTransOffset = 4;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(18) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% q_2dsfl_pos_cntrl_DW.BiasRemoval.EnabledMovingAverage_MODE
	  section.data(1).logicalSrcIdx = 72;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(19) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (dwork)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    dworkMap.nTotData = nTotData;
    


  ;%
  ;% Add individual maps to base struct.
  ;%

  targMap.paramMap  = paramMap;    
  targMap.signalMap = sigMap;
  targMap.dworkMap  = dworkMap;
  
  ;%
  ;% Add checksums to base struct.
  ;%


  targMap.checksum0 = 689154293;
  targMap.checksum1 = 892160550;
  targMap.checksum2 = 3195933216;
  targMap.checksum3 = 1561247154;

