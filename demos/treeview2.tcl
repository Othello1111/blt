#!../src/bltwish

set count 0
package require BLT
#source scripts/demo.tcl

proc SortColumn { column } {
    set old [.t sort cget -column] 
    set decreasing 0
    if { "$old" == "$column" } {
	set decreasing [.t sort cget -decreasing]
	set decreasing [expr !$decreasing]
    }
    .t sort configure -decreasing $decreasing -column $column -mode integer
    if { ![.t cget -flat] } {
	.t configure -flat yes
    }
    .t sort auto yes

    blt::busy hold .t
    update
    blt::busy release .t
}

proc FormatSize { size } {
   set string ""
   while { $size > 0 } {
       set rem [expr $size % 1000]
       set size [expr $size / 1000]
       if { $size > 0 } {
           set rem [format "%03d" $rem]
       } 
       if { $string != "" } {
           set string "$rem,$string"
       } else {
           set string "$rem"
       }
   } 
   return $string
}

array set modes {
   0	---
   1    --x
   2    -w-
   3    -wx
   4    r-- 
   5    r-x
   6    rw-
   7    rwx
}

proc FormatMode { mode } {
   global modes

   set mode [format %o [expr $mode & 07777]]
   set owner $modes([string index $mode 0])
   set group $modes([string index $mode 1])
   set world $modes([string index $mode 2])

   return "${owner}${group}${world}"
}

proc Find { tree parent dir } {
    global count 
    set saved [pwd]

    cd $dir
    foreach f [lsort [glob -nocomplain *]] {
	set name [file tail $f]
	    
	if { [catch { file lstat $f info }] != 0 } {
	    if { ![$tree exists $parent->"$name"] } {
		set node [$tree insert $parent -label $name]
	    }
	} else {
	    if 0 {
	    if { $info(type) == "file" } {
		set info(type) [list @blt::TreeView::openIcon $name]
	    } else {
		set info(type) "@blt::TreeView::openIcon "
	    }
	    }
	    set info(mtime) [clock format $info(mtime) -format "%b %d, %Y"]
	    set info(atime) [clock format $info(atime) -format "%b %d, %Y"]
	    set info(ctime) [clock format $info(ctime) -format "%b %d, %Y"]
            set info(owner)  [file attributes $name -owner]
            set info(group)  [file attributes $name -group]
            set info(size)  [FormatSize $info(size)]
	    set info(mode)  [file attributes $name -permissions]
	    if { ![$tree exists $parent->"$name"] } {
		set node [$tree insert $parent -label $name \
			      -data [array get info]]
	    } else {
		set node [$tree findchild $parent $name]
		puts "already found $f"
	    }
	}
	incr count
	if { [file type $f] == "directory" } {
	    .t entry configure $node -button yes 
	}
    }
    cd $saved
}

proc GetAbsolutePath { dir } {
    set saved [pwd]
    cd $dir
    set path [pwd] 
    cd $saved
    return $path
}

set top [GetAbsolutePath .]
set trim "$top"

set tree [blt::tree create]    
scrollbar .vs -orient vertical -command { .t yview }
scrollbar .hs -orient horizontal -command { .t xview }

proc OpenNode  { tree node parent top } {
    if { [file type $parent] == "directory" } {
	blt::busy hold .t
	Find $tree $node $top/$parent
	update
	blt::busy release .t
    }
}

proc CloseNode  { tree node } {
    eval $tree delete [$tree children $nodex]
}


blt::treeview .t \
    -width 0 \
    -yscrollcommand { .vs set } \
    -xscrollcommand { .hs set } \
    -selectmode multiple \
    -separator / \
    -tree $tree \
    -opencommand [list OpenNode $tree %\# %P $top]  \
    -closecommand [list CloseNode $tree %\#]

set img [image create picture -data {
    R0lGODlhEAANAMIAAAAAAH9/f///////AL+/vwAA/wAAAAAAACH5BAEAAAUALAAAAAAQAA0A
    AAM1WBrM+rAEMigJ8c3Kb3OSII6kGABhp1JnaK1VGwjwKwtvHqNzzd263M3H4n2OH1QBwGw6
    nQkAOw==
}]
	 
update
.t column configure treeView -text "" 
#file
.t column insert 0 mtime atime ctime 
.t column insert end nlink mode type owner group ino size dev
.t column configure owner 
.t column configure mtime -hide no
.t column configure size group nlink owner ino dev -justify left -edit yes
.t column configure size type -justify left -edit yes
.t column configure treeView -hide no -edit no -icon $img
focus .t


blt::table . \
    0,0 .t  -fill both \
    0,1 .vs -fill y \
    1,0 .hs -fill x
blt::table configure . c1 r1 -resize none

puts "$count entries"

#$tree find root -glob *.c -addtag "c_files"
#$tree find root -glob *.h -addtag "header_files"
#$tree find root -glob *.tcl -addtag "tcl_files"

#.t entry configure "c_files" -foreground green4
#.t entry configure "header_files" -foreground cyan4
#.t entry configure "tcl_files" -foreground red4 

.t column bind all <ButtonRelease-3> {
    %W configure -flat no
}

foreach column [.t column names] {
    .t column configure $column -command [list SortColumn $column]
}

# Create a second treeview that shares the same tree.
if 0 {
toplevel .top
blt::treeview .top.t2 -tree $tree -yscrollcommand { .top.sbar set }
scrollbar .top.sbar -command { .top.t2 yview }
pack .top.t2 -side left -expand yes -fill both
pack .top.sbar -side right -fill y
}

#.t style configure text -background #F8fbF8 -selectbackground #D8fbD8 

.t style checkbox check \
    -onvalue 30 -offvalue "50" \
    -showvalue yes 

.t style combobox combo -icon $img

#.t column configure owner -style combo 
#.t column configure group -style check

