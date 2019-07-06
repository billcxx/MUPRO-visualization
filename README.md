# MUPRO-visualization

This is a open source visualization software. This software is build based on Qt, vtk and qcustomplot. 
Currently, I'm the only one in charge of this project, and it is almost of pure personal interest, without any consideration of suitable license.
Since I'm still developing it, and I don't think it is ready for anyone to use.

One reason I put it online is to use github to keep track of my code, and another reason is I find it might be useful for some of you, who
are also doing Qt+vtk development and very likely you're already frustrated with the documentation on the vtk side, I hope my project can 
be a small example that might help some of you with your problems (if you can bear my poor programming style). 
So feel free to read the code, but please don't distribute the code to anyone else, since I haven't consider about license yet, and I don't
want to be in trouble.

# Mac
```brew install vtk```, this will install both vtk and qt!

To deploy on mac, make sure you're using the correct macdeployqt, there is another one in anaconda
```/usr/local/opt/qt/bin/macdeployqt SimpleView.app```
