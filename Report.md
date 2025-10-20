Report Milestone 1 & 2: Segment Detection Analysis.

With all regards, imma send u the log too :

Total Windows Terdeteksi (3x3): 374748
--- Pola Window Unik Ditemukan ( 61 ) ---
"000"
"000"
"001"
"000"
"000"
"011"
"000"
"000"
"111"
"000"
"000"
"110"
"000"
"000"
"100"
"000"
"001"
"111"
"000"
"011"
"111"
"000"
"111"
"111"
"000"
"110"
"111"
"000"
"100"
"111"
"000"
"001"
"011"
"001"
"111"
"111"
"011"
"111"
"111"
"111"
"111"
"111"
"110"
"111"
"111"
"100"
"111"
"111"
"000"
"100"
"110"
"001"
"011"
"111"
"100"
"110"
"111"
"000"
"001"
"001"
"001"
"011"
"011"
"100"
"110"
"110"
"000"
"100"
"100"
"001"
"001"
"011"
"011"
"011"
"111"
"110"
"110"
"111"
"100"
"100"
"110"
"001"
"001"
"001"
"011"
"011"
"011"
"110"
"110"
"110"
"100"
"100"
"100"
"001"
"001"
"000"
"011"
"011"
"001"
"111"
"111"
"011"
"111"
"111"
"110"
"110"
"110"
"100"
"100"
"100"
"000"
"001"
"000"
"000"
"011"
"001"
"001"
"111"
"011"
"011"
"111"
"110"
"110"
"110"
"100"
"100"
"100"
"000"
"000"
"011"
"001"
"000"
"111"
"011"
"001"
"111"
"110"
"100"
"110"
"100"
"000"
"111"
"011"
"000"
"111"
"111"
"001"
"111"
"111"
"100"
"111"
"110"
"000"
"011"
"000"
"000"
"111"
"001"
"000"
"111"
"111"
"000"
"111"
"100"
"000"
"110"
"000"
"000"
"111"
"000"
"000"
"000"
"110"
"110"
"110"
"110"
"000"
"000"
"011"
"011"
"011"
"011"
"000"
--- Segment Detection Selesai ---


1. Ideal Window Size Determination (Goal 1)

The chosen window size for local feature detection is 3×3.

Justification

The 3×3 size is selected as the ideal window because:

    Efficiency and Scope: It provides an optimal balance between computational efficiency and the scope needed to capture relevant features.

    Key Feature Capture: This size is the minimum necessary to accurately capture and differentiate the fundamental geometric components of a segment, including a 3-pixel straight line, a corner (junction), and a segment endpoint. Using a larger window would unnecessarily complicate the pattern analysis with non-local information.

2. Ideal Binary Pattern Analysis (Goal 2)

Analysis Method

The detection process analyzed 374,748 windows, identifying 61 unique, non-empty 3×3 binary patterns from the drawn canvas data. The analysis focuses on patterns that exhibit strong pixel connectivity (3 or more connected pixels) to define a valid segment feature.

Ideal Patterns Used for Filtering (The Detector Set)

The function isSegmentPattern(bool x[3][3]) is built upon these ideal patterns. This ensures the filter is highly specific and excludes isolated noise, successfully fulfilling Goal 3 implementation.

Complete Straight Line	010 / 010 / 010 (Vertical Center) 000 / 111 / 000 (Horizontal Center)	Provides the highest confidence that the window is centered over a continuous, straight segment.

Diagonal Line	100 / 010 / 001 (Diagonal Down-Right)	Represents a continuous diagonal segment.

Segment Endpoint	000 / 110 / 000 (Horizontal End, right side)	Marks the final point of a segment, critical for defining object boundaries.

Corner/Junction	110 / 100 / 000 (Top-Left Corner)	Detects a change in segment direction or a connection point.

3. Implementation of the Automated Detector (Goal 3)

Filtering Strategy

The automatic detector is implemented by integrating the identified ideal patterns into the logic of the isSegmentPattern() function. This function serves as the sole filter within DrawingCanvas::segmentDetection(), ensuring that only patterns matching the analyzed criteria are accepted.

Solution Verification

Every time a window successfully matches one of the ideal patterns, its coordinates are recorded. This successful detection is then visualized on the canvas by drawing a 3×3 purple rectangle over the candidate region, directly verifying the correctness of the implemented detection algorithm.