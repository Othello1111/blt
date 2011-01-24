package require BLT
package require Tk

set a [frame .a -bg red]
set tree [::blt::treeview $a.tree\
	 -bg blue \
         -relief flat -bd 10 \
         -selectmode single\
         -exportselection false]
$tree configure -yscrollcommand "$a.y set" -xscrollcommand "$a.x set"
scrollbar $a.y -command "$tree yview"
scrollbar $a.x -command "$tree xview" -orient horizontal
grid $tree -row 0 -column 1 -sticky nsew
grid $a.y -row 0 -column 2 -sticky ns
grid $a.x -row 1 -column 1 -sticky we
grid columnconfigure $a 1 -weight 1
grid rowconfigure $a 0 -weight 1

$tree configure -width 0
$tree column configure treeView -width 0
$tree insert end hello -label hello
#$tree insert end a -label aaaaaaaaaaaaaaaaaaaaaaaaaaaaa

 pack $a -fill both -expand true
