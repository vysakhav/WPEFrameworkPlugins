#ifndef WPEFRAMEWORK_PLUGIN_RTSPCOMMON_H
#define WPEFRAMEWORK_PLUGIN_RTSPCOMMON_H


#define KB(x)   (x*1000)
#define MB(x)   (x*1000)

namespace WPEFramework {
namespace Plugin {

enum RtspReturnCode {
    ERR_OK,
    ERR_UNKNOWN,
    ERR_ACTIVE,
    ERR_NO_ACTIVE_SESSION,
    ERR_CONNECT_FAILED,
    ERR_SESSION_FAILED,
    ERR_NO_MORE,
    ERR_TIMED_OUT,

};


class RtspMessage
{
    public:
    enum Type {
        RTSP_REQUEST,
        RTSP_RESPONSE,
        RTSP_ANNOUNCE,
        RTSP_UNKNOWN
    };

    virtual RtspMessage::Type getType()
    {
        return RTSP_UNKNOWN;
    }

    public:
    //RtspMessage::Type _type;
    string message;
    bool bSRM;                          // true: to/from SRM, false: to/from Pump
};

typedef std::shared_ptr<RtspMessage> RtspMessagePtr;

class RtspRequst : public RtspMessage
{
    public:
    RtspRequst()
        : bStreamRequest(false)
    {
    }

    virtual ~RtspRequst()
    {
    }

    RtspMessage::Type getType()
    {
        return RTSP_REQUEST;
    }
    bool bStreamRequest;
};

class RtspResponse : public RtspMessage
{
    public:
        RtspResponse(uint16_t code)
            : _code (code)
        {
        }

        ~RtspResponse()
        {
        }

        RtspMessage::Type getType()
        {
            return RTSP_RESPONSE;
        }

    private:
        uint16_t _code;
        uint32_t _sequence;
};

class RtspAnnounce : public RtspMessage
{
    public:
       enum Code {
            PlayoutStalled              = 1103,
            PlayoutResumed              = 1104,
            NewScale                    = 1500,
            EosReached                  = 2101,
            BosReached                  = 2104,
            StreamStateChange           = 2199,
            TicketExpired               = 2401,
            SessionTornDown_heartbeat   = 2403,
            SessionTornDown             = 2406,
            DataError                   = 4400,
            SvrRsrcNotAvailable         = 5200,
            InternalServerError         = 5502,
            ServerShutdown              = 5403,
            StreamChange                = 5999
        };


         RtspAnnounce(uint16_t code, string reason)
            : _code (code)
            , _reason(reason)
        {
        }
        ~RtspAnnounce()
        {
        }
        RtspMessage::Type getType()
        {
            return RTSP_ANNOUNCE;
        }
        uint16_t GetCode() const
        {
            return _code;
        }
        string GetReason() const
        {
            return _reason;
        }

    private:
        uint16_t _code;
        string _reason;
};


}} // WPEFramework::Plugin

#endif
