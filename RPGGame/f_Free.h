int FObj()
{	
	int Obj = 0;
	bool Found = false;
	while ( !Found )
	{
		Obj++;
		if ( dbObjectExist( Obj ) == 0 ) Found = true;
	}
	return Obj;
}

int FLig()
{	
	int Obj = 0;
	bool Found = false;
	while ( !Found )
	{
		Obj++;
		if ( dbLightExist( Obj ) == 0 ) Found = true;
	}
	return Obj;
}

int FImg()
{	
	int Img = 0;
	bool Found = false;
	while ( !Found )
	{
		Img++;
		if ( dbImageExist( Img ) == 0 ) Found = true;
	}
	return Img;
}

int FMat()
{
	int Mat = 0;
	bool Found = false;
	while ( !Found )
	{
		Mat++;
		if ( dbImageExist( Mat ) == 0 ) Found = true;
	}
	return Mat;
}

int FCam()
{
	int Cam = 0;
	bool Found = false;
	while ( !Found )
	{
		Cam++;
		if ( dbImageExist( Cam ) == 0 ) Found = true;
	}
	return Cam;
}

int FLim(int Object)
{
	int Lim = 0;
	bool Found = false;
	while ( !Found )
	{
		Lim++;
		if ( dbLimbExist(Object, Lim ) == 0 ) Found = true;
	}
	return Lim;
}

int FMes()
{
	int Mes = 0;
	bool Found = false;
	while ( !Found )
	{
		Mes++;
		if ( dbMeshExist( Mes ) == 0 ) Found = true;
	}
	return Mes;
}