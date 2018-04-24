#include <ndn-cxx/face.hpp>
using namespace ndn;

#include <iostream>

int main(int argc, char** argv)
{
  Face faceToNFD;
 
  auto onData = [] (const Interest& interest, const Data& data) {
    std::cout << " << D: " << data << std::endl;
  };
  auto onNack = [] (const Interest& interest, const lp::Nack& nack) {
    std::cout << "received Nack with reason " << nack.getReason() << std::endl;    
  };
  TimeoutCallback onTimeout = [&] (const Interest& interest) {
    std::cout << "interest timeout, retransmit it" << std::endl;
    faceToNFD.expressInterest(Interest(interest.getName()).setMustBeFresh(true),
			      onData, onNack, onTimeout);
  };

  Interest interest(Name("/cs217/100/test-data/101"), 1_s);
  interest.setMustBeFresh(true);
  
  faceToNFD.expressInterest(interest, onData, onNack, onTimeout);
  faceToNFD.processEvents();
  
  return 0;
}
