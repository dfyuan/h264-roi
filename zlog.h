#ifndef ZLOG_H
#define ZLOG_H

#include "zlogworker.h"

#define ZLOG_DEBUG_DEPTH 100

#define LOG(A)  LibChaos::ZLog() << A
#define DLOG(A) LibChaos::ZLog() << LibChaos::ZLog::debug << A
#define RLOG(A) LibChaos::ZLog() << LibChaos::ZLog::raw << A
#define ELOG(A) LibChaos::ZLog() << LibChaos::ZLog::error << A
#define SLOG(A) LibChaos::ZLog() << LibChaos::ZLog::sync << A
#define OLOG(A) LibChaos::ZLog() << LibChaos::ZLog::stdio << A
#define ORLOG(A) OLOG(LibChaos::ZLog::raw << A)

#define LG  LibChaos::ZLog()
#define DLG LibChaos::ZLog() << LibChaos::ZLog::debug
#define RLG LibChaos::ZLog() << LibChaos::ZLog::plain_this
#define ELG LibChaos::ZLog() << LibChaos::ZLog::error
#define OLG LibChaos::ZLog() << LibChaos::ZLog::stdio
#define SLG LibChaos::ZLog() << LibChaos::ZLog::sync

#define IF_LOG(A, B, C, D) if(A){ LOG( B << C ); } else { LOG( B << D ); }
#define IF_DLOG(A, B, C, D) if(A){ DLOG( B << C ); } else { DLOG( B << D ); }

namespace LibChaos {

class ZLog {
public:
    enum zlog_flags {
        flush = 1,      // Manual call to flush log
        newln = 2,      // Append newline to buffer
        flushln = 3,    // Manual call to flush log after appending new newline
        noln = 4,       // Skip next automatic newline
        raw = 5,        // This object will log without formatting

        normal = 6,     // Set instance of class to log normally
        debug = 7,      // Set instance of class to log to debug buffer
        error = 8,      // Current instance to logs and outputs to stderr

        stdio = 9,      // Current instance outputs only to stdout

        sync = 10,      // Log immediately, block until done
        async = 11      // Push log to queue, return as soon as possible
    };

    ZLog();
    ~ZLog();

    ZLog &operator<<(zlog_flags);
    ZLog &log(ZString logtext);
    ZLog &operator<<(ZString text);
    ZLog &operator<<(std::string text);
    ZLog &operator<<(zs64 text);
    ZLog &operator<<(const char *text);
    ZLog &operator<<(char *text);
    ZLog &operator<<(ZPath text);
    ZLog &operator<<(ZBinary text);
    ZString pullBuffer();

    static ZString getTime();
    static ZString getClock();
    static ZString getThread();
    static ZString genLogFileName(ZString prefix);

    static void init();
    static void init(ZPath);

    static void formatStdout(ZlogFormat normal, ZlogFormat debug, ZlogFormat error);
    static void formatStderr(ZlogFormat normal, ZlogFormat debug, ZlogFormat error);
    static void addLogFile(ZPath, ZlogFormat normal, ZlogFormat debug, ZlogFormat error);
private:
    void flushLog();

    static bool _init;
    static ZLogWorker worker;
    static AsArZ thread_ids;

    ZString buffer;
    char source_mode; // normal = 0, debug = 1, error = 2
    bool stdout_this;
    bool write_on_destruct;
    bool newline;
    bool rawlog;
    bool priority;

};

//typedef ZLog::Worker ZLogWorker;

} // namespace LibChaos

#endif // ZLOG_H
