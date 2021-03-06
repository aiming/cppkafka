/*
 * Copyright (c) 2017, Matias Fontanini
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "topic.h"

using std::move;
using std::string;

namespace cppkafka {

void dummy_topic_destroyer(rd_kafka_topic_t*) {

}

Topic Topic::make_non_owning(rd_kafka_topic_t* handle) {
    return Topic(handle, NonOwningTag{});
}

Topic::Topic() 
: handle_(nullptr, nullptr) {

}

Topic::Topic(rd_kafka_topic_t* handle) 
: handle_(handle, &rd_kafka_topic_destroy) {

}

Topic::Topic(rd_kafka_topic_t* handle, NonOwningTag)
: handle_(handle, &dummy_topic_destroyer) {

}

string Topic::get_name() const {
    return rd_kafka_topic_name(handle_.get());
}

bool Topic::is_partition_available(int partition) const {
    return rd_kafka_topic_partition_available(handle_.get(), partition);
}

rd_kafka_topic_t* Topic::get_handle() const {
    return handle_.get();
}

} // cppkafka
