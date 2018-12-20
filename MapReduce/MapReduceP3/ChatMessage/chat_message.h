#ifndef CHAT_MESSAGE_H
#define CHAT_MESSAGE_H
#include <cstdio>
#include <cstdlib>
#include <cstring>
/*
this message format start with 3 length digit char as length of
the data. Tt use strncat and memcpy to decode and incode header.
Need to include _CRT_SECURE_NO_WARNINGS in preprocessor to use
these unsafe functions.
*/
class ChatMessage {
public:
	enum { header_length = 4 };
	enum { max_body_length = 512 };
	ChatMessage()
		: body_length_(0){}
	const char* data() const {
		return data_;
	}
	char* GetMyData() {
		return data_;
	}
	std::size_t GetMyLength() const {
		return header_length + body_length_;
	}
	const char* GetMyBody() const {
		return data_ + header_length;
	}
	char* GetMyBody() {
		return data_ + header_length;
	}
	std::size_t GetBodyLength() const {
		return body_length_;
	}
	void SetBodyLength(std::size_t new_length) {
		body_length_ = new_length;
		if (body_length_ > max_body_length)
			body_length_ = max_body_length;
	}
	bool DecodeHeader() {
		char header[header_length + 1] = "";
		std::strncat(header, data_, header_length);
		body_length_ = std::atoi(header);
		if (body_length_ > max_body_length) {
			body_length_ = 0;
			return false;
		}
		return true;
	}
	void EncodeHeader() {
		char header[header_length + 1] = "";
		std::sprintf(header, "%4d", static_cast<int>(body_length_));
		std::memcpy(data_, header, header_length);
	}
private:
	char data_[header_length + max_body_length];
	std::size_t body_length_;
};

#endif // CHAT_MESSAGE_H