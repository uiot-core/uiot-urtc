#include "URTCConfig.h"
#include "RTCEngineFactory.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

#include "URTCMsgHandler.h"
#include "msgqueue.h"
#include <iostream>
#include "RTCVideoFrameSource.h"

URTCMsgHandler* g_msghandler = nullptr ;

int main(int argc, char **argv)
{
	std::string roomid = "afnyhnizq9l4l9ev";
	std::string userid = "afnyhnizq9l4l9ev_camera3" ;
	std::string tokenid = "eyJhcHBfaWQiOiJ1cnRjLTRtYjB0dW9yIiwicm9vbV9pZCI6ImFmbnlobml6cTlsNGw5ZXYiLCJ1c2VyX2lkIjoiYWZueWhuaXpxOWw0bDlldl9jYW1lcmEzIn0=.fc4d0c1d202a6f749eb84b1df846dcd06b102a171578648069f0c5341e";
	std::string cmd = "" ;
	std::string rtspurl = "" ;
	
	if(argc>=2) 
	{
		rtspurl = argv[1];
		std::cout <<"input rtsp url "<< rtspurl <<std::endl ;
	}

	if(argc>=3) 
	{
		roomid = argv[2];
		std::cout <<"input roomid "<< roomid <<std::endl ;
	}
	if(argc>=4) 
	{
		userid = argv[3];
		std::cout <<"input userid "<< userid <<std::endl ;
	}
	
	RTCEngineBase* urtcengine = RTCEngineFactory::createRtcEngine(RTC_CHANNELTYPE_UCLOUD);
	UCloudRtcExtendVideoCaptureSource * videocap = new VideoFrameSource();
	if (urtcengine)
	{
		g_msghandler = new URTCMsgHandler(urtcengine) ;
		MsgQueue::getInstance()->regEventHandler("", g_msghandler);
		MsgQueue::getInstance()->startMsgQue() ;
        	urtcengine->InitRTCEngine("./data/log", 0);
		urtcengine->enableExtendVideoSource(true, videocap);
		//urtcengine->EnableRtspSource(1, true, rtspurl) ;
		g_msghandler->setUserId(roomid) ;
        	g_msghandler->setRoomId(userid) ;


		tRTCAuthInfo auth;
		auth.mAppid = URTCConfig::getInstance()->getAppId();
		auth.mRoomid = roomid;
		auth.mUserid = userid ;
		auth.mToken = tokenid;
		urtcengine->JoinRoom(auth);	
		while (true)
		{
			usleep(1000*1000) ;
		}
	}
    return 0;
}


