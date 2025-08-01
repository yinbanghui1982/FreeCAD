#include "TdmsParser.h"
#include "TdmsGroup.h"
#include "TdmsChannel.h"
#include <math.h>
#include <string.h>
#include <cstdlib>

void help()
{
	std::cout << "Use: tdmsreader -option your_file_name.tdms" << std::endl;
	std::cout << "Options:" << std::endl;
	std::cout << "-h: print help information and exit" << std::endl;
	std::cout << "-p: display channel properties" << std::endl;
	std::cout << "-s: store channel data values" << std::endl;
	std::cout << "-v: verbose output" << std::endl;
}

void errorMessage()
{
	std::cout << "\nInput error: please provide a single valid *.tdms file name!" << std::endl;
}

int main(int argc, char *argv[])
{
	std::cout << "\nNational Instruments TDMS file reader by Ion Vasilief (C) 2017 - 2020" << std::endl;

	if (argc < 2){
		std::cout << "Use: tdmsreader your_file_name.tdms" << std::endl;
		errorMessage();
		return 0;
	}

	if ((argc == 2) && (strcmp(argv[1], "-h") == 0)){
		help();
		exit(0);
	}

	bool verbose = false, storeValues = false, showProperties = false;
	if ((argc == 3) && (strchr(argv[1], '-'))){
		if (strchr(argv[1], 'p'))
			showProperties = true;
		if (strchr(argv[1], 's'))
			storeValues = true;
		if (strchr(argv[1], 'v'))
			verbose = true;
	}

	std::string fileName = (argc == 3) ? argv[2] : argv[1];
	TdmsParser parser(fileName, storeValues);
	if (parser.fileOpeningError()){
		errorMessage();
		return 0;
	}

	parser.read(verbose);

	unsigned int groupCount = parser.getGroupCount();
	printf("\nNumber of groups: %d\n", groupCount);
	for (unsigned int i = 0; i < groupCount; i++){
		TdmsGroup *group = parser.getGroup(i);
		if (!group)
			continue;

		unsigned int channelsCount = group->getGroupSize();
		if (channelsCount)
			printf("\nGroup %s (%d/%d) has %d channels:\n\n", group->getName().c_str(), i + 1, groupCount, channelsCount);
		else
			printf("\nGroup %s (%d/%d) has 0 channels.\n", group->getName().c_str(), i + 1, groupCount);

		for (unsigned int j = 0; j < channelsCount; j++){
			TdmsChannel *ch = group->getChannel(j);
			if (ch){
				unsigned long long dataCount = ch->getDataCount(), stringCount = ch->getStringCount();
				unsigned long long dataSize = (dataCount > 0) ? dataCount : stringCount;
				string unit = ch->getUnit();
				if (unit.empty())
					printf("%d) Channel %s has %lld values\n", j + 1, ch->getName().c_str(), dataSize);
				else
					printf("%d) Channel %s (unit: %s) has %lld values\n", j + 1, ch->getName().c_str(), unit.c_str(), dataSize);

				unsigned int type = ch->getDataType();

				if (dataCount){
					std::vector<double> data = ch->getDataVector();
					if ((type == TdmsChannel::tdsTypeComplexSingleFloat) || (type == TdmsChannel::tdsTypeComplexDoubleFloat)){
						std::vector<double> imData = ch->getImaginaryDataVector();
						if (!imData.empty()){
							double iVal1 = imData.front(), iVal2 = imData.back();
							std::string fmt = "\t%g";
							fmt.append((iVal1 < 0) ? "-i*%g ... %g" : "+i*%g ... %g");
							fmt.append((iVal2 < 0) ? "-i*%g\n" : "+i*%g\n");
							printf(fmt.c_str(), data.front(), fabs(iVal1), data.back(), fabs(iVal2));
						}
					} else {
						if (!data.empty())
							printf("\t[begin...end]: %g ... %g\n", data.front(), data.back());

						printf("\t[min...max]: %g ... %g\n", ch->getMinDataValue(), ch->getMaxDataValue());

						if (dataCount)
							printf("\taverage data value: %g\n", ch->getDataSum()/dataCount);
					}
				} else if (stringCount){
					std::vector<std::string> strings = ch->getStringVector();
					if (!strings.empty()){
						string str1 = strings.front();
						if (str1.empty())
							str1 = "empty string";
						string str2 = strings.back();
						if (str2.empty())
							str2 = "empty string";
						printf(":\n\t%s ... %s\n", str1.c_str(), str2.c_str());
					}
				}

				if (showProperties)
					printf("and %d properties:\n%s\n", ch->getPropertyCount(), ch->propertiesToString().c_str());

				if (storeValues)
					ch->freeMemory();
			}
		}
	}

	printf("\nSuccessfully parsed file '%s' (size: %lld bytes).\n", fileName.c_str(), parser.fileSize());
	printf("Done!\n");
	return 0;
}
