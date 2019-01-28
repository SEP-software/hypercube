#pragma once
#include<string>
class SEPException : public std::exception {
public:
    explicit SEPException(std::string  m) : message{m} {}
    virtual const char * what() const noexcept override {return message.c_str();}
    std::string getMessage()const {return message;}
private:
    std::string message = "";
};
