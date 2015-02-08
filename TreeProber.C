#include <iostream>
#include <string>
#include <TTree.h>
#include <TFile.h>
//#include "probe_tree.h"

using namespace std;

int TreeProber(){
//	std::string infile("ggfHZG_20bx25_private.root");
//	std::string infile("ggfHZG_20bx25_private_numEvent4000.root");
//	std::string infile("ggfHZG_20bx25_CSA14_numEvent4000.root");
//		std::string infile("ggfHZG_20bx25_CSA14.root");
//	std::string infile("/afs/cern.ch/work/r/rateixei/work/LatinosHZGamma/commit/CMSSW_7_2_0/src/LatinoTrees/AnalysisStep/test/ggfHgg_20bx25_phys14.root");
//	std::string infile("/afs/cern.ch/work/r/rateixei/work/LatinosHZGamma/commit/CMSSW_7_2_0/src/LatinoTrees/AnalysisStep/test/ggfHgg_20bx25_phys14_all_2photons.root");
//	std::string infile("/afs/cern.ch/work/r/rateixei/work/LatinosHZGamma/commit/CMSSW_7_2_0/src/LatinoTrees/AnalysisStep/test/ggfHzg_20bx25_csa14_all.root");
	std::string infile("/afs/cern.ch/work/r/rateixei/work/LatinosHZGamma/commit/CMSSW_7_2_0/src/LatinoTrees/AnalysisStep/test/ggfHzg_private_20bx25_phys14_all_2photons_2.root");
	std::string Root(".root");
	TString IF(infile);
	std::size_t found = infile.find(Root);
	if(found==std::string::npos){
		cout << "Root file name invalid" << endl;
		return 0;
	} else {
//		TFile* file = new TFile("ggfHZG_20bx25_private.root", "READ");
		TFile* file = new TFile(IF, "READ");
		TTree* t = (TTree*) file->Get("Tree/probe_tree");
		t->Process("src/probe_tree.C", "hzg_private_phys14_probe_2phos_2.root");
		cout << "Processing tree with " << t->GetEntriesFast() << " entries..." << endl;
	}
}
/*
int main(int argc, char **argv){
	if(argc != 2){
		cout << "Give an input file, please..." << endl;
		return 0;
	}
	TreeProber(argv[1]);
	return 0;
}*/
