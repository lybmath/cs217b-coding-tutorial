#include <ndn-cxx/face.hpp>
#include <ndn-cxx/security/key-chain.hpp>
#include <iostream>
using namespace ndn;

int main(int argc, char** argv)
{ 
  Face faceToNFD;
  KeyChain appKeyChain;
  appKeyChain.createIdentity("/cs217/100");

  Name dataName("/cs217/100/test-data");
  auto onInterest = [&] (const InterestFilter& filter, const Interest& interest) {
    std::cout << "<< I: " << interest << std::endl;

    Data data(dataName);
    appKeyChain.sign(data);
    
    faceToNFD.put(data);
  };
  
  auto onFailure = [] (const Name& prefix, const std::string& reason) {
    std::cout << "fail to register " << prefix << " due to: " << reason << std::endl;
  };

  faceToNFD.setInterestFilter(dataName, onInterest, onFailure);
  faceToNFD.processEvents();
  
  return 0;
}

/*
|------------------------------------------------------------------------------|
| Set InterestFilter to dispatch incoming matching interest to onInterest      |
| callback and register the filtered prefix with the connected NDN forwarder   |
|------------------------------------------------------------------------------|
  const RegisteredPrefixId*
  setInterestFilter(const InterestFilter& interestFilter,
                    const InterestCallback& onInterest,
                    const RegisterPrefixFailureCallback& onFailure,
                    const security::SigningInfo& signingInfo = security::SigningInfo(),
                    uint64_t flags = nfd::ROUTE_FLAG_CHILD_INHERIT);

|------------------------------------------------------------------------------|
| Construct an InterestFilter to match Interests by prefix                     |  
|------------------------------------------------------------------------------|
  InterestFilter(const Name& prefix)
 
|------------------------------------------------------------------------------|
| Callback invoked when incoming Interest matches the specified InterestFilter |
|------------------------------------------------------------------------------|
  typedef function<void(const InterestFilter&, const Interest&)> InterestCallback;

|------------------------------------------------------------------------------|
| Callback invoked when registerPrefix or setInterestFilter command fails      |
|------------------------------------------------------------------------------|
  typedef function<void(const Name&, const std::string&)> RegisterPrefixFailureCallback;

*/
