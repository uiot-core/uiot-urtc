#include "RTCVideoFrameSource.h"
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <errno.h>

VideoFrameSource::~VideoFrameSource() {
	if(m_fd != -1)
	{
		close(m_fd);
	}
}

int VideoFrameSource::openFile()
{
    struct stat statbuff;
    char *filepath = "./resource/suzie_qcif.y4m";

    if(m_fd == -1)
    {
        m_fd = open(filepath, O_RDONLY);
        if(m_fd<0)
        {
		std::cout <<"open file error"<< errno<< std::endl;
            close(m_fd);
            return -1;
        }
        stat(filepath, &statbuff);
        m_filesize = statbuff.st_size;
        lseek(m_fd, 44L, SEEK_SET);
	m_filersize = 44;
    }
	
    if(m_filesize<=m_filersize)
    {
        lseek(m_fd, 44L, SEEK_SET);
	m_filersize = 44;
    }
    return 0;

}

bool VideoFrameSource::doCaptureVideoFrame(tUCloudRtcVideoFrame* videoframe)
{
    int width = 176 ;
    int height = 144 ;
    int size = 176*144*3/2 ;
    int ret=-1;
    int len = 0;
    int pos = 0;
    int copysize = 0;
    char buf[1024]= {0};
    char *strret;
    videoframe->mWidth = width ;
    videoframe->mHeight = height ;
    videoframe->mDataSize = size ;
    videoframe->mVideoType = UCLOUD_RTC_VIDEO_FRAME_TYPE_I420 ;
    ret = openFile();
    if(ret == -1)
    {
        return false;
    }

    do {
	    len=read(m_fd, buf, 1024);
	    m_filersize +=len;
	    strret = strstr(buf, "FRAME\n");
	    if(strret==NULL)
	    {
		    memcpy(videoframe->mDataBuf+copysize,buf,len);
		    copysize+=len;
	    }
	    else
	    {
		   pos = strret -buf; 
		   memcpy(videoframe->mDataBuf+copysize,buf,pos);
		   copysize+=pos;
		   m_filersize -=(len-pos-6);
		   lseek(m_fd, m_filersize, SEEK_SET);
		   break;
	    }
	    if(m_filersize>=m_filesize)
	    {
		    break;
	    }
    } while(true);
    return true;
};

