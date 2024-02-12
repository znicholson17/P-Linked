SamacSys ECAD Model
984532/1324675/2.50/2/3/Ferrite Bead

DESIGNSPARK_INTERMEDIATE_ASCII

(asciiHeader
	(fileUnits MM)
)
(library Library_1
	(padStyleDef "r100_90"
		(holeDiam 0)
		(padShape (layerNumRef 1) (padShapeType Rect)  (shapeWidth 0.9) (shapeHeight 1))
		(padShape (layerNumRef 16) (padShapeType Ellipse)  (shapeWidth 0) (shapeHeight 0))
	)
	(textStyleDef "Default"
		(font
			(fontType Stroke)
			(fontFace "Helvetica")
			(fontHeight 50 mils)
			(strokeWidth 5 mils)
		)
	)
	(patternDef "BEADC1608X95N" (originalName "BEADC1608X95N")
		(multiLayer
			(pad (padNum 1) (padStyleRef r100_90) (pt -0.8, 0) (rotation 0))
			(pad (padNum 2) (padStyleRef r100_90) (pt 0.8, 0) (rotation 0))
		)
		(layerContents (layerNumRef 18)
			(attr "RefDes" "RefDes" (pt 0, 0) (textStyleRef "Default") (isVisible True))
		)
		(layerContents (layerNumRef 30)
			(line (pt -1.5 0.75) (pt 1.5 0.75) (width 0.05))
		)
		(layerContents (layerNumRef 30)
			(line (pt 1.5 0.75) (pt 1.5 -0.75) (width 0.05))
		)
		(layerContents (layerNumRef 30)
			(line (pt 1.5 -0.75) (pt -1.5 -0.75) (width 0.05))
		)
		(layerContents (layerNumRef 30)
			(line (pt -1.5 -0.75) (pt -1.5 0.75) (width 0.05))
		)
		(layerContents (layerNumRef 28)
			(line (pt -0.8 0.4) (pt 0.8 0.4) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt 0.8 0.4) (pt 0.8 -0.4) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt 0.8 -0.4) (pt -0.8 -0.4) (width 0.1))
		)
		(layerContents (layerNumRef 28)
			(line (pt -0.8 -0.4) (pt -0.8 0.4) (width 0.1))
		)
		(layerContents (layerNumRef 18)
			(line (pt 0 0.3) (pt 0 -0.3) (width 0.2))
		)
	)
	(symbolDef "PE-0603PFB121ST" (originalName "PE-0603PFB121ST")

		(pin (pinNum 1) (pt 0 mils 0 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -25 mils) (rotation 0]) (justify "Left") (textStyleRef "Default"))
		))
		(pin (pinNum 2) (pt 0 mils -100 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -125 mils) (rotation 0]) (justify "Left") (textStyleRef "Default"))
		))
		(line (pt 200 mils 100 mils) (pt 600 mils 100 mils) (width 6 mils))
		(line (pt 600 mils 100 mils) (pt 600 mils -200 mils) (width 6 mils))
		(line (pt 600 mils -200 mils) (pt 200 mils -200 mils) (width 6 mils))
		(line (pt 200 mils -200 mils) (pt 200 mils 100 mils) (width 6 mils))
		(attr "RefDes" "RefDes" (pt 650 mils 300 mils) (justify Left) (isVisible True) (textStyleRef "Default"))

	)
	(compDef "PE-0603PFB121ST" (originalName "PE-0603PFB121ST") (compHeader (numPins 2) (numParts 1) (refDesPrefix FB)
		)
		(compPin "1" (pinName "1") (partNum 1) (symPinNum 1) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(compPin "2" (pinName "2") (partNum 1) (symPinNum 2) (gateEq 0) (pinEq 0) (pinType Bidirectional))
		(attachedSymbol (partNum 1) (altType Normal) (symbolName "PE-0603PFB121ST"))
		(attachedPattern (patternNum 1) (patternName "BEADC1608X95N")
			(numPads 2)
			(padPinMap
				(padNum 1) (compPinRef "1")
				(padNum 2) (compPinRef "2")
			)
		)
		(attr "Manufacturer_Name" "Pulse Electronics")
		(attr "Manufacturer_Part_Number" "PE-0603PFB121ST")
		(attr "Mouser Part Number" "673-PE-0603PFB121ST")
		(attr "Mouser Price/Stock" "https://www.mouser.co.uk/ProductDetail/Pulse-Electronics/PE-0603PFB121ST?qs=mXcQpiKXIAzgd58UAlJe4A%3D%3D")
		(attr "Arrow Part Number" "PE-0603PFB121ST")
		(attr "Arrow Price/Stock" "https://www.arrow.com/en/products/pe-0603pfb121st/pulse-electronics-corporation?region=nac")
		(attr "Description" "Ferrite Beads 0603 120Ohms SMT FERRITE CHIP BEAD")
		(attr "Datasheet Link" "https://www.arrow.com/en/products/pe-0603pfb121st/pulse-electronics-corporation?region=nac")
		(attr "Height" "0.95 mm")
	)

)
