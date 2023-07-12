{

    printf("\n");
    if (gSystem->Load("libProof.so")!=0) {
	printf("Shared library libProof.so could not load\n");
    }
    if (gSystem->Load("libTreePlayer.so")!=0) {
	printf("Shared library libTreePlayer.so could not load\n");
    }
    if (gSystem->Load("libPhysics.so")!=0) {
	printf("Shared library libPhysics.so could not load\n");
    }
    
    if (getenv("PLUTO_DIR") == NULL) {
	if (gSystem->Load("../../../builddir/libPluto.so")==0) {
	    printf("Shared library Pluto.so loaded\n");
	} else {
	    printf("Unable to load Pluto.so\n");
	}
    } else {
	if (gSystem->Load("$PLUTO_DIR/lib64/libPluto.so")==0) {
	    printf("Shared library Pluto.so loaded\n");
	} else {
	    printf("Unable to load Pluto.so\n");
	} 
    }

}







