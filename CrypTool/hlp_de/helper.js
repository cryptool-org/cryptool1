function parser(fn)
{
	//
	// flomar, 06/03/09: quick fix for EXTERNAL file links
	//
	// if we have an external link (i.e. starting with "http://")  
	// as parameter in "fn", then directly set this link as our href
	// (without the usual "C:/foo/bar/yadayada" relative stuff that is 
	// causing dead links for external file links).
 
	if(fn.substring(0, 7) == "http://") {
		link = fn;
		location.href = link;
	}

	else {
		var X, Y, sl, a, ra, link;
		ra = /:/;
		a = location.href.search(ra);
		if (a == 2) X = 14;
		else X = 7;
		sl = "\\";
		Y = location.href.lastIndexOf(sl) + 1;
		link = 'file:///' + location.href.substring(X, Y) + fn;
		location.href = link;

	}

}