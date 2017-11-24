#ifndef SMALLPROJECTS_STATUS_H
#define SMALLPROJECTS_STATUS_H

#include <string>
#include "export.h"
#include "slice.h"

class LEVELDB_EXPORT Status {
public:
    // Create a success status
    Status() : state_(nullptr) {}
    ~Status() { delete[] state_; }

    // Copy the specified status
    Status(const Status& s);
    void operator=(const Status& s);

    // Return the specified status.
    static Status OK() { return Status(); }

    // Return error status of an appropriate type.
    static Status NotFound(const Slice& msg, const Slice& msg2 = Slice()) {
        return Status(kNotFound, msg, msg2);
    }

    static Status Corruption(const Slice& msg, const Slice& msg2 = Slice()) {
        return Status(kCorruption, msg, msg2);
    }

    static Status InvalidArgument(const Slice& msg, const Slice& msg2 = Slice()) {
        return Status(kInvalidArgument, msg, msg2);
    }

    static Status NotSupported(const Slice& msg, const Slice& msg2 = Slice()) {
        return Status(kNotSupported, msg, msg2);
    }

    static Status IOError(const Slice& msg, const Slice& msg2 = Slice()) {
        return Status(kIOError, msg, msg2);
    }

    // Returns true iff the status indicates success.
    bool ok() const { return (state_ == NULL); }

    // Returns true iff the status indicates a NotFound error.
    bool IsNotFound() const { return code() == kNotFound; }

    // Returns true iff the status indicates a Corruption error.
    bool IsCorruption() const { return code() == kCorruption; }

    // Returns true iff the status indicates an IOError
    bool IsIOError() const { return code() == kIOError; }

    // Returns true iff the status indicates a NotSupportedError.
    bool IsNotSupportedError() const { return code() == kNotSupported; }

    // Returns true iff the status indicates an InvalidArgument.
    bool IsInvalidArgument() const { return code() == kInvalidArgument; }

    // Return a string representation of this status suitable for printing.
    // Returns the string "OK" for success.
    std::string ToString() const;

private:
    // Ok status has a NULL state_. Otherwise, state_ is a new[] array
    // ok the following form:
    // state_[0..3] == length of message
    // state_[4]    == code

    const char* state_;

    enum Code {
        kOK = 0,
        kNotFound = 1,
        kCorruption = 2,
        kNotSupported = 3,
        kInvalidArgument = 4,
        kIOError = 5
    };

    Code code() const {
        return (state_ == nullptr) ? kOK : static_cast<Code>(state_[4]);
    }


    Status(Code code, const Slice& msg, const Slice& msg2);
    static const char* CopyState(const char* s);



};


inline Status::Status(const Status& s) {
    state_ = (s.state_ == NULL) ? NULL : CopyState(s.state_);
}

inline void Status::operator=(const Status& s) {
    // The following condition cathches both alising (when this = &s),
    // and the common case where both s and *this are ok.
    if(state_ != s.state_) {
        delete [] state_;
        state_ = (s.state_ == NULL) ? NULL : CopyState(s.state_);
    }
}



#endif //SMALLPROJECTS_STATUS_H
