#!/bin/python

from ROOT import *
from PrintTH1F import *
from Efficiency import *
from Compare import *
import getopt, sys

def main(argv):
	ROOT.gROOT.SetBatch()
	inputfile = ''
	outputfile = ''
	legend = ''
	effs = ''
	normalize = ''
	try:
		opts, args = getopt.getopt(argv,"hi:o:l:c:n:",["input=","output=", "legend=", "compare=", "normalize="])
	except getopt.GetoptError:
		print 'test.py -i <inputfile> -o <outputfile> -l <legend> -e "h_pass:h_total'
		sys.exit(2)
	for opt, arg in opts:
		if opt == '-h':
			print 'test.py -i <inputfile> -o <outputfile>'
			sys.exit()
		elif opt in ("-i", "--input"):
			inputfile = arg
		elif opt in ("-o", "--output"):
			outputfile = arg
		elif opt in ("-l", "--legend"):
			legend = arg
		elif opt in ("-c", "--compare"):
			effs = arg
		elif opt in ("-n", "--normalize"):
			effs = arg

	if inputfile == '':
		print "Specify input file: test.py -i <inputfile>"
		sys.exit()
	if effs == '':
		print "Specify which plots to make! -e 'h_pass/h_total, g_pass/g_total...'"
		sys.exit()
	if legend == '':
		print "Please specify two legends: -l 'Legend 1:Legend 2'"
		sys.exit()
	if outputfile == '':
		outputfile = 'output.root'
	if normalize == '':
		normalize = 0

	hists = effs.split(',')

	print 'Input file is ', inputfile
	print 'Output file is ', outputfile
	print 'Legend for all histograms is ', legend	
	print 'Producing following plot: ', hists

	file = TFile(inputfile, 'READ')
	list = file.GetListOfKeys()

	for st in hists:
		passName = str(st.split(':')[0]).strip()
		IsPass = 0
		totalName = str(st.split(':')[1]).strip()
		IsTotal = 0
		for x in xrange(0, list.GetEntries()):
			if passName == str(list[x].GetName()):
				IsPass = 1
			if totalName == str(list[x].GetName()):
				IsTotal = 1 
		if (IsPass == 0) or (IsTotal == 0):
			print "Couldn't find hists in file...", passName, totalName
			continue

		print "Getting hists: ", passName, totalName
		h_pass = file.Get(passName)
		print "h_pass has integral: ", h_pass.Integral()
		h_total = file.Get(totalName)
		print "h_total has integral: ", h_total.Integral()
		
		CompareTH1F(h_pass,h_total,legend,normalize)
		
if __name__ == "__main__":
	main(sys.argv[1:])
