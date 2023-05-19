#pragma once

namespace csgrpc {
    class CsGrpcVersion final {
        public:
            CsGrpcVersion(int major, int minor)
            :   _major(major),
                _minor(minor)
            {}

            CsGrpcVersion(const CsGrpcVersion& other)
            :   _major(other._major),
                _minor(other._minor)
            {}

            CsGrpcVersion(const CsGrpcVersion&& other)
            :   _major(other._major),
                _minor(other._minor)
            {}

            virtual ~CsGrpcVersion() = default;

            CsGrpcVersion& operator=(const CsGrpcVersion& other) {
                if (this != &other) {
                    this->_major = other._major;
                    this->_minor = other._minor;
                }
                return *this;
            }

            bool operator==(const CsGrpcVersion& other) {
                return (this == &other) ||
                    (this->_major == other._major &&
                     this->_minor == other._minor);
            }

            int GetMajorVersion() {
                return _major;
            }

            int GetMinorVersion() {
                return _minor;
            }
        private:
            int _major;
            int _minor;
    };
}