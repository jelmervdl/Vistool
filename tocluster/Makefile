XML = $(wildcard *.xml)
LOG = $(XML:.xml=.log)

all: $(LOG)

$(LOG): %.log: %.xml
	cd ..; ./machineVisionTool -p tocluster/$*.xml cluster abdullah2010 tocluster/$* > tocluster/$*.log
	cd ..; ./machineVisionTool -C tocluster/$* optimize >> tocluster/$*.log
	cd ..; ./machineVisionTool -C tocluster/$* experiment nn abdullah2010 1000 >> tocluster/$*.log
	cd ..; ./machineVisionTool -C tocluster/$* experiment svm abdullah2010 1000 >> tocluster/$*.log