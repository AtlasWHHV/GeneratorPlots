// Generate plots from a xAOD file that has the EVNT banks in it.
//
// Usage:
//    PlotGeneratorQanitites
//

// GitHubProgramCode added
#include "xAODRootAccess/Init.h"
#include "SampleHandler/SampleHandler.h"
#include "SampleHandler/ScanDir.h"
#include "SampleHandler/ToolsDiscovery.h"
#include "EventLoop/Job.h"
#include "EventLoop/DirectDriver.h"
#include "SampleHandler/DiskListLocal.h"
#include <TSystem.h>


// GitHubProgramCode added
#include "GeneratorPlotsAlt/MyxAODAnalysis.h"

#include <iostream>
#include <string>

using namespace std;

// int main()
// {
//   cout << "hi" << endl;
// }


// GitHubProgramCode added
int main( int argc, char* argv[] ) {
  
  // // GitHubProgramCode added
  cout << "hi" << endl;

  // Take the submit directory from the input if provided:
  std::string submitDir = "submitDir";
  if( argc > 1 ) submitDir = argv[ 1 ];

  // Set up the job for xAOD access:
  xAOD::Init().ignore();

  // Construct the samples to run on:
  SH::SampleHandler sh;

  // use SampleHandler to scan all of the subdirectories of a directory for particular MC single file:
  const char* inputFilePath = gSystem->ExpandPathName ("/phys/groups/tev/scratch4/users/nicolasNDS/20170201_Run/");
  SH::ScanDir().filePattern("DAOD_SUSY1.08377960._000012.pool.root.1").scan(sh,inputFilePath);


  // Set the name of the input TTree. It's always "CollectionTree"
  // for xAOD files.
  sh.setMetaString( "nc_tree", "CollectionTree" );

  // Print what we found:
  sh.print();

  // Create an EventLoop job:
  EL::Job job;
  job.sampleHandler( sh );
  job.options()->setDouble (EL::Job::optMaxEvents, 500);

  // Add our analysis to the job:
  MyxAODAnalysis* alg = new MyxAODAnalysis();
  job.algsAdd( alg );

  // Run the job using the local/direct driver:
  EL::DirectDriver driver;
  driver.submit( job, submitDir );

  return 0;
}