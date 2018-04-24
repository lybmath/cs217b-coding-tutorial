#include <ndn-cxx/face.hpp>
#include <ndn-cxx/security/key-chain.hpp>
using namespace ndn;

#include <iostream>
#include <unordered_map>

int main(int argc, char** argv)
{ 
  Face faceToNFD;
  KeyChain appKeyChain;
  appKeyChain.createIdentity("cs217/100");

  uint64_t sequenceNo = 0;
  std::unordered_map<Name, uint64_t> requesterCount;
  auto onInterest = [&] (const InterestFilter& filter, const Interest& interest) {
    auto requester = interest.getName().getSubName(-1);
    requesterCount[requester] ++;
    
    std::cout << " << " << requesterCount[requester] << " Interest(s) from " << requester << std::endl; 
    if (requesterCount[requester] % 3 != 0) return;

    shared_ptr<Data> data = make_shared<Data>(Name(interest.getName()).appendNumber(++ sequenceNo));
    appKeyChain.sign(*data);

    faceToNFD.put(*data);
  };
  auto onFailure = [] (const Name& prefix, const std::string& reason) {
    std::cout << "fail to register " << prefix << " due to: " << reason << std::endl;
  };

  faceToNFD.setInterestFilter("/cs217/100/test-data", onInterest, onFailure);
  faceToNFD.processEvents();
  
  return 0;
}
