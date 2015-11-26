
ardclean:
	rm -r ~/ardpj/sketchbook/libraries/DMD795x2

zipit:
	zip DMD795x2.zip *.h *.cpp -r examples

zipclean:
	rm DMD795x2.zip
