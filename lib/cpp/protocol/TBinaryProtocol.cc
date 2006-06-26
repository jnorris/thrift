#include "protocol/TBinaryProtocol.h"
using std::string;

uint32_t TBinaryProtocol::writeStructBegin(TTransport* out,
                                           const string& name) const {
  return 0;
}

uint32_t TBinaryProtocol::writeStructEnd(TTransport* out) const {
  return 0;
}

uint32_t TBinaryProtocol::writeFieldBegin(TTransport* out,
                                          const string& name,
                                          const TType fieldType,
                                          const uint16_t fieldId) const {
  return
    writeByte(out, (uint8_t)fieldType) +
    writeI32(out, (int32_t)fieldId);
}

uint32_t TBinaryProtocol::writeFieldEnd(TTransport* out) const {
  return 0;
}

uint32_t TBinaryProtocol::writeFieldStop(TTransport* out) const {
  return
    writeByte(out, (uint8_t)T_STOP);
}  
                               
uint32_t TBinaryProtocol::writeMapBegin(TTransport* out,
                                        const TType keyType,
                                        const TType valType,
                                        const int32_t size) const {
  return
    writeByte(out, (uint8_t)keyType) +
    writeByte(out, (uint8_t)valType) +
    writeI32(out, (int32_t)size);
}

uint32_t TBinaryProtocol::writeMapEnd(TTransport* out) const {
  return 0;
}

uint32_t TBinaryProtocol::writeListBegin(TTransport* out,
                                         const TType elemType,
                                         const int32_t size) const {
  return
    writeByte(out, (uint8_t) elemType) +
    writeI32(out, (int32_t)size);
}

uint32_t TBinaryProtocol::writeListEnd(TTransport* out) const {
  return 0;
}

uint32_t TBinaryProtocol::writeSetBegin(TTransport* out,
                                        const TType elemType,
                                        const int32_t size) const {
  return
    writeByte(out, (uint8_t)elemType) +
    writeI32(out, (int32_t)size);
}

uint32_t TBinaryProtocol::writeSetEnd(TTransport* out) const {
  return 0;
}

uint32_t TBinaryProtocol::writeByte(TTransport* out,
                                    const uint8_t byte) const {
  out->write(&byte, 1);
  return 1;
}

uint32_t TBinaryProtocol::writeU32(TTransport* out,
                                   const uint32_t u32) const {
  uint32_t net = (uint32_t)htonl(u32);
  out->write((uint8_t*)&net, 4);
  return 4;
}

uint32_t TBinaryProtocol::writeI32(TTransport* out,
                                   const int32_t i32) const {
  int32_t net = (int32_t)htonl(i32);
  out->write((uint8_t*)&net, 4);
  return 4;
}

uint32_t TBinaryProtocol::writeU64(TTransport* out,
                                   const uint64_t u64) const {
  uint64_t net = (uint64_t)htonll(u64);
  out->write((uint8_t*)&net, 8);
  return 8;
}

uint32_t TBinaryProtocol::writeI64(TTransport* out,
                                   const int64_t i64) const {
  int64_t net = (int64_t)htonll(i64);
  out->write((uint8_t*)&net, 8);
  return 8;
}

uint32_t TBinaryProtocol::writeString(TTransport* out,
                                      const string& str) const {
  uint32_t result = writeI32(out, str.size());
  out->write((uint8_t*)str.data(), str.size());
  return result + str.size();
}

/**
 * Reading functions
 */

uint32_t TBinaryProtocol::readStructBegin(TTransport* in,
                                          string& name) const {
  name = "";
  return 0;
}

uint32_t TBinaryProtocol::readStructEnd(TTransport* in) const {
  return 0;
}

uint32_t TBinaryProtocol::readFieldBegin(TTransport* in,
                                         string& name,
                                         TType& fieldType,
                                         uint16_t& fieldId) const {
  uint32_t result = 0;
  uint8_t type;
  result += readByte(in, type);
  fieldType = (TType)type;
  if (fieldType == T_STOP) {
    fieldId = 0;
    return result;
  }
  int32_t id;
  result += readI32(in, id);
  fieldId = (uint16_t)id;
  return result;
}
  
uint32_t TBinaryProtocol::readFieldEnd(TTransport* in) const {
  return 0;
}
 
uint32_t TBinaryProtocol::readMapBegin(TTransport* in,
                                       TType& keyType,
                                       TType& valType,
                                       int32_t& size) const {
  uint8_t k, v;
  uint32_t result = 0;
  result += readByte(in, k);
  keyType = (TType)k;
  result += readByte(in, v);
  valType = (TType)v;
  result += readI32(in, size);
  return result;
}

uint32_t TBinaryProtocol::readMapEnd(TTransport* in) const {
  return 0;
}

uint32_t TBinaryProtocol::readListBegin(TTransport* in,
                                        TType& elemType,
                                        int32_t& size) const {
  uint8_t e;
  uint32_t result = 0;
  result += readByte(in, e);
  elemType = (TType)e;
  result += readI32(in, size);
  return result;
}

uint32_t TBinaryProtocol::readListEnd(TTransport* in) const {
  return 0;
}

uint32_t TBinaryProtocol::readSetBegin(TTransport* in,
                                       TType& elemType,
                                       int32_t& size) const {
  uint8_t e;
  uint32_t result = 0;
  result += readByte(in, e);
  elemType = (TType)e;
  result += readI32(in, size);
  return result;
}

uint32_t TBinaryProtocol::readSetEnd(TTransport* in) const {
  return 0;
}

uint32_t TBinaryProtocol::readByte(TTransport* in,
                                   uint8_t& byte) const {
  uint8_t b[1];
  in->readAll(b, 1);
  byte = *(uint8_t*)b;
  return 1;
}

uint32_t TBinaryProtocol::readU32(TTransport* in,
                                  uint32_t& u32) const {
  uint8_t b[4];
  in->readAll(b, 4);
  u32 = *(uint32_t*)b;
  u32 = (uint32_t)ntohl(u32);
  return 4;
}

uint32_t TBinaryProtocol::readI32(TTransport* in,
                                  int32_t& i32) const {
  uint8_t b[4];
  in->readAll(b, 4);
  i32 = *(int32_t*)b;
  i32 = (int32_t)ntohl(i32);
  return 4;
}

uint32_t TBinaryProtocol::readU64(TTransport* in,
                                  uint64_t& u64) const {
  uint8_t b[8];
  in->readAll(b, 8);
  u64 = *(uint64_t*)b;
  u64 = (uint64_t)ntohll(u64);
  return 8;
}

uint32_t TBinaryProtocol::readI64(TTransport* in,
                                  int64_t& i64) const {
  uint8_t b[8];
  in->readAll(b, 8);
  i64 = *(int64_t*)b;
  i64 = (int64_t)ntohll(i64);
  return 8;
}

uint32_t TBinaryProtocol::readString(TTransport* in,
                                     string& str) const {
  uint32_t result;
  int32_t size;
  result = readI32(in, size);
  uint8_t b[size];
  in->readAll(b, size);
  str = string((char*)b, size);
  return result + (uint32_t)size;
}
