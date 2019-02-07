function doSelection(table, len)
{
	for( var i = 0; i < len; i++ )
	{
		var child = table.children[i];
		var tr = child.getElementsByTagName("tr")[1];
		if( tr )
		{
			var radio = tr.getElementsByTagName("input")[0];
			radio.click();
		}
	}
}

function doTextarea(tale, len)
{
	for( var i = 0; i < len; i++ )
	{
		var child = table.children[i];
		var td_list = child.getElementsByTagName("td");
		var td_len = td_list.length;
		var td = td_list[td_len - 1];
		var textarea = td.getElementsByTagName("textarea")[0]
		textarea.value = "好";
	}
}

var ifm = document.getElementsByTagName("iframe")[0];
var doc = ifm.contentDocument;
var table = doc.getElementById("ext-gen56");
var len = table.children.length;
doSelection(table, len);
doTextarea(table, len);
