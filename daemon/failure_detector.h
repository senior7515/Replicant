// Copyright (c) 2012, Robert Escriva
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright notice,
//       this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of Replicant nor the names of its contributors may be
//       used to endorse or promote products derived from this software without
//       specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef replicant_daemon_failure_detector_h_
#define replicant_daemon_failure_detector_h_

// C
#include <stdint.h>

// STL
#include <deque>
#include <memory>

// e
#include <e/intrusive_ptr.h>

namespace replicant
{

class failure_detector
{
    public:
        failure_detector(uint64_t now, uint64_t ping_pong, uint64_t window_sz);
        ~failure_detector() throw ();

    public:
        uint64_t seqno();
        void heartbeat(uint64_t seqno, uint64_t now);
        double suspicion(uint64_t now);

    private:
        class ping;
        friend class e::intrusive_ptr<failure_detector>;
        void inc() { ++m_ref; }
        void dec() { if (--m_ref == 0) delete this; }

    private:
        const std::auto_ptr<std::deque<ping> > m_window;
        uint64_t m_window_sz;
        uint64_t m_interval;
        size_t m_ref;
};

} // namespace replicant

#endif // replicant_daemon_failure_detector_h_
