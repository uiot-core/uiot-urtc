#ifndef _UMEETING_URTCENGINEIMPL_H_
#define _UMEETING_URTCENGINEIMPL_H_

#include "UCloudRtcComDefine.h"

class VideoFrameSource : public UCloudRtcExtendVideoCaptureSource {
public:
	virtual ~VideoFrameSource();
        virtual  bool doCaptureVideoFrame(tUCloudRtcVideoFrame* videoframe);
		private:
			int openFile();
			int m_fd = -1;
			int m_lseekoffset = 0;
			unsigned long m_filesize = 0;
			unsigned long m_filersize = 0;
}; 


#endif

