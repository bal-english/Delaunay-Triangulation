-----------------
 Important Notes
-----------------
	The makefile for this project will create two applications. Both execute the same process to calculate the delaunay triangulation; however they differ in the ways in which they display them.
		delaunay_app:
			- Utilizes the third-party graphics library, "SFML", to display the triangulation in an application window.
			- IMPORTANT: The application window does not have an "exit" button like most windows. Use Alt+F4 to exit the application (or stop it in the console window).
		delaunay_imagemaker:
			- Saves the triangulation to a NetPBM Portable BitMap File. Most Linux machines can read open these files by default. However, if you are unable to open it, you can use this web app: http://paulcuth.me.uk/netpbm-viewer/

	If you do not have the required dependencies and libraries for SFML, some precompiled executables can be found in this zip.

-------------------
 Application Usage
-------------------
	The application generates a set of random points. You can specify the number of points to generate for the triangulation via:
		./executable_name numberOfPoints

	However, you can also leave that field empty to use the default of number of points: 5.
		./executable_name
