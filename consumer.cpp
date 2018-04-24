#include <ndn-cxx/face.hpp>
#include <iostream>
using namespace ndn;

int main(int argc, char** argv)
{
  Face faceToNFD;
  Interest interest(Name("/cs217/100/test-data"));
  interest.setMustBeFresh(true);
 
  auto onData = [] (const Interest& interest, const Data& data) {
    std::cout << " << D: " << data << std::endl;
  };
  auto onNack = [] (const Interest& interest, const lp::Nack& nack) {
    std::cout << "received Nack with reason " << nack.getReason() << std::endl;    
  };
  auto onTimeout = [] (const Interest& interest) {
    std::cout << "interest timeout " << std::endl;
  };

  faceToNFD.expressInterest(interest, onData, onNack, onTimeout);
  faceToNFD.processEvents();
  
  return 0;
}

/*
|------------------------------------------------------------------------------|
| Express Interest                                                             |
|------------------------------------------------------------------------------|
  const PendingInterestId*
  expressInterest(const Interest& interest,
                  const DataCallback& afterSatisfied,
                  const NackCallback& afterNacked,
                  const TimeoutCallback& afterTimeout);

|------------------------------------------------------------------------------|
| Callback invoked when expressed Interest gets satisfied with a Data packet   |  
|------------------------------------------------------------------------------|
  typedef function<void(const Interest&, const Data&)> DataCallback;
 
|------------------------------------------------------------------------------|
| Callback invoked when Nack is sent in response to expressed Interest         |
|------------------------------------------------------------------------------|
  typedef function<void(const Interest&, const lp::Nack&)> NackCallback;

|------------------------------------------------------------------------------|
| Callback invoked when expressed Interest times out                           |
|------------------------------------------------------------------------------|
  typedef function<void(const Interest&)> TimeoutCallback;

*/
