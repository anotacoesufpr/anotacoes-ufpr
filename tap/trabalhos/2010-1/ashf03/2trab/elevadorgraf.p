
2e6 -> popmemlim;

exload_batch;

uses-now Xm;
uses-now Xpw;

loadinclude xpt_coretypes.ph;
loadinclude XmConstants.ph;

loadinclude XpwPixmap;

uses switchon;

global vars procedure tree_to_string;

uses
    xt_init,
    xt_widget,
    xt_widgetclass,
    xt_widgetinfo,
    xt_composite,
    xt_popup,
    xt_event,
    xt_callback,
    xt_resource,

    xtTopLevelShellWidget,
    xmTextFieldWidget,
    xmListWidget,
    xmFormWidget,
    xmRowColumnWidget,
    xmCascadeButtonWidget,
    xmCascadeButtonGadget,
    xmPushButtonWidget,
    xmSeparatorWidget,
    xmScrollBarWidget,
    xmScrolledWindowWidget,

    XpwPixmap,
    xpwGraphicWidget,
    xpwCompositeWidget,

    XptShellDeleteResponse,
    XptBusyCursorFeedback,
    XptGarbageCursorFeedback,

    xpm_listutils,
;

endexload_batch;


defclass rui_layout_window {
    rlw_parent,
    rlw_shell,
    rlw_menubar,
    rlw_filemenu,
    rlw_editmenu,
    rlw_helpmenu,
    rlw_galleryarea,
    rlw_gallerybuttons,
    rlw_scrollarea,
    rlw_composite,
    rlw_drawarea,
    rlw_footer,
    rlw_on_close,
};


/* --------------------------------------------------------------------
    Window
   -------------------------------------------------------------------- */

define DisplayWin(win_data);
 lvars win_data, shell;

    XtPopup((win_data.rlw_shell ->> shell), 0);

    if win_data.rlw_on_close then
        erase <> win_data.rlw_on_close
    else
        erase
    endif -> XptShellDeleteResponse(shell);
enddefine;



define ClearDrawing(win_data); lvars win_data, shell;

    XpwClearWindow(win_data.rlw_drawarea);
enddefine;



/* --------------------------------------------------------------------
    Status Line
   -------------------------------------------------------------------- */

define SetFooter(msg, win_data);
 lvars win_data, msg, footer = win_data.rlw_footer;

    XptCheckString(msg) -> XptVal footer(XtN value:XptString);
enddefine;



define ClearFooter(w);
 lvars w;

    SetFooter(' ', w)
enddefine;


define DeferAction(p);
lvars p;

    XptDeferApply(p);
    XptSetXtWakeup();
enddefine;


define NotifyClose(w, win_data, call);
    lvars w, win_data, call;

    if isprocedure(win_data.rlw_on_close) then
        DeferAction(win_data.rlw_on_close);
    endif;
enddefine;


constant
    FILECB_NEW      = 1,
    FILECB_OPEN     = 2,
    FILECB_SAVE     = 3,
    FILECB_SAVEAS   = 4,
    FILECB_CLOSE    = 5,
;

define filemenu_cb(w, client, call);
    lvars w, client, call;

    go_on client to NEW OPEN SAVE SAVEAS CLOSE;

    NEW:
        return;

    OPEN:
        return;

    SAVE:
        return;

    SAVEAS:
        return;

    CLOSE:
        return;
enddefine;


constant
    EDITCB_UNDO     = 1,
    EDITCB_CUT      = 2,
    EDITCB_COPY     = 3,
    EDITCB_PASTE    = 4,
    EDITCB_DELETE   = 5,
;

define editmenu_cb(w, client, call);
    lvars w, client, call;

    go_on client to UNDO CUT COPY PASTE DELETE;

    UNDO:
        return;

    CUT:
        return;

    COPY:
        return;

    PASTE:
        return;

    DELETE:
        return;
enddefine;


constant
    HELPCB_ONTOOL   = 1,
    HELPCB_ONRUI    = 2,
;

define helpmenu_cb(w, client, call);
    lvars w, client, call;

    go_on client to ONTOOL ONRUI;

    ONTOOL:
        return;

    ONRUI:
        return;
enddefine;


/* --------------------------------------------------------------------
    Menu Definitions
   -------------------------------------------------------------------- */

constant
    menuSeparator = {^nullstring ^nullstring ^false ^false},
    fileMenu = 'fileMenu',
    editMenu = 'editMenu',
    helpMenu = 'helpMenu',
;

constant
    file_menu_buttons = {
        'Arquivo'
        ^fileMenu
        ^filemenu_cb
        {^(fileMenu <> 'newButton') 'Novo...'        ^true   ^FILECB_NEW}
        {^(fileMenu <> 'openButton') 'Abrir...'      ^false  ^FILECB_OPEN}
        ^menuSeparator
        {^(fileMenu <> 'saveButton') 'Salvar'         ^false  ^FILECB_SAVE}
        {^(fileMenu <> 'saveAsButton') 'Salvar Como...' ^false  ^FILECB_SAVEAS}
        ^menuSeparator
        {^(fileMenu <> 'closeButton') 'Fechar'       ^false  ^FILECB_CLOSE}
    },

    edit_menu_buttons = {
        'Editar'
        ^editMenu
        ^editmenu_cb
        {^(editMenu <> 'undoButton')    'Desfazer'  ^false  ^EDITCB_UNDO}
        ^menuSeparator
        {^(editMenu <> 'cutButton')     'Cortar'   ^true   ^EDITCB_CUT}
        {^(editMenu <> 'copyButton')    'Copiar'  ^false  ^EDITCB_COPY}
        {^(editMenu <> 'pasteButton')   'Colar' ^false  ^EDITCB_PASTE}
        ^menuSeparator
        {^(editMenu <> 'deleteButton')  'Apagar' ^false ^EDITCB_DELETE}
    },

    help_menu_buttons = {
        'Ajuda'
        ^helpMenu
        ^helpmenu_cb
        {^(helpMenu <> 'onToolButton')  'Geral'  ^true    ^HELPCB_ONTOOL}
        {^(helpMenu <> 'onRUIButton')   'Buscar'   ^false   ^HELPCB_ONRUI}
    },
;


/* --------------------------------------------------------------------
    Gallery Button Handlers
   -------------------------------------------------------------------- */

constant
    GALLERY_INPUT_BTN       = 1,
    GALLERY_DRAWING_BTN     = 2,
    GALLERY_TREE_BTN        = 3,
;

define gallerybutton_cb(w, client, call);
    lvars w, client, call;

    go_on client to INPUT DRAWING TREE;

    INPUT:
        return;

    DRAWING:
        return;

    TREE:
        return;
enddefine;


/* --------------------------------------------------------------------
    Gallery Button Definitions
   -------------------------------------------------------------------- */

constant
    galleryArea = 'gallery',
;

constant
    gallery_buttons = {
        ^gallerybutton_cb
        {^(galleryArea <> 'inputButton')    'Subparte'     ^GALLERY_INPUT_BTN}
        {^(galleryArea <> 'drawingButton')  'Editar'   ^GALLERY_DRAWING_BTN}
        {^(galleryArea <> 'treeButton')     'Apagar'      ^GALLERY_TREE_BTN}
    },
;


/* --------------------------------------------------------------------
    Window Creation Routine
   -------------------------------------------------------------------- */

define create_menu_buttons(parent, desc, pre_cb)
                            -> menu -> button;
lvars parent, desc, pre_cb, menu, button;

    XmCreatePulldownMenu(parent, 'menu_pane', XptArgList([])) -> menu;
    XtVaCreateManagedWidget(subscrv(2, desc), xmCascadeButtonGadget,
        parent, (#| XmN subMenuId, menu |#)) -> button;
    subscrv(1, desc) -> XptVal button(XmN labelString:XmString);

    if pre_cb then
        XtAddCallback(button, XmN cascadingCallback, pre_cb, menu);
    endif;
enddefine;


define add_menu_button(parent, name, label, default, client, cb);
    lvars parent, name, label, default, client, cb, button;

    if label = nullstring then
        XtVaCreateManagedWidget(label, xmSeparatorWidget, parent,
                    #| |#) -> ;
    else
        XtVaCreateManagedWidget(name, xmPushButtonWidget, parent,
                    #|
                        XmN default, default,
                    |#) -> button;
        label -> XptVal button(XmN labelString:XmString);
        XtAddCallback(button, XmN activateCallback, cb, client);
    endif;
enddefine;


define add_menu_buttons(desc, menu);
lvars desc, menu, menu_cb, button;

    subscrv(3, desc) -> menu_cb;
    fast_for button in_vector desc do
        if isvector(button) then
            add_menu_button(menu, explode(button), menu_cb)
        endif;
    endfast_for;
enddefine;


define add_gallery_buttons(buttons, gallery) -> button_list;
lvars buttons, gallery, button_list, button_cb, button_desc, button;

    subscrv(1, buttons) -> button_cb;
    [% fast_for button_desc in_vector buttons do
        if isvector(button_desc) then
            XtVaCreateManagedWidget(subscrv(1, button_desc),
                    xmPushButtonWidget, gallery,
                    #|
                        XmN default, false,
                    |#) -> button;
            subscrv(2, button_desc) -> XptVal button(XmN labelString:XmString);
            XtAddCallback(button, XmN activateCallback, button_cb,
                    subscrv(3, button_desc));
            button;
        endif;
    endfast_for; %] -> button_list;
enddefine;


define make_layout_window(file_desc, edit_desc, help_desc,
    menuprepare_cb, gallery_buttons,
    on_close, ref_widget) -> layout_window;

lvars
    file_desc, edit_desc, help_desc,
    menuprepare_cb, gallery_buttons,
    on_close, ref_widget, layout_window;

    consrui_layout_window(dupnum(false, 13)) -> layout_window;

    ref_widget -> layout_window.rlw_parent;

    if isprocedure(on_close) then
        on_close -> layout_window.rlw_on_close;
    endif;

    lvars shell;
    XtVaCreatePopupShell('layoutWindow', xtTopLevelShellWidget, ref_widget,
        #|
            XtN title, 'Editor de Hierarquias',
            XtN deleteResponse, XmUNMAP,
        |# ) ->> shell -> layout_window.rlw_shell;

    lvars form;
    XtVaCreateManagedWidget('form', xmFormWidget, shell,
        #|
            XmN fractionBase, 10,
        |# ) -> form;

    lvars menubar;
    XmCreateMenuBar(form, 'menubar',
        XptArgList([
                {orientation ^XmHORIZONTAL}
                {topAttachment ^XmATTACH_FORM}
                {leftAttachment ^XmATTACH_FORM}
                {rightAttachment ^XmATTACH_FORM}
            ])) ->> menubar ->layout_window.rlw_menubar;
    XtManageChild(menubar);

    lvars file_menu, file_widget;
    create_menu_buttons(menubar, file_desc, menuprepare_cb)
        ->> file_menu -> layout_window.rlw_filemenu
        -> file_widget;


    lvars edit_menu, edit_widget;
    create_menu_buttons(menubar, edit_desc, menuprepare_cb)
        ->> edit_menu -> layout_window.rlw_editmenu
        -> edit_widget;

    lvars help_menu, help_widget;
    create_menu_buttons(menubar, help_desc, menuprepare_cb)
        ->> help_menu -> layout_window.rlw_helpmenu
        -> help_widget;

    help_widget -> XptVal menubar(XmN menuHelpWidget:XptWidget);

    add_menu_buttons(file_desc, file_menu);
    add_menu_buttons(edit_desc, edit_menu);
    add_menu_buttons(help_desc, help_menu);


    lvars gallery;
    XtVaCreateManagedWidget('gallery', xmRowColumnWidget, form,
        #|
            XmN leftAttachment, XmATTACH_FORM,
            XmN rightAttachment, XmATTACH_FORM,
            XmN topAttachment, XmATTACH_WIDGET,
            XmN topWidget, menubar,
            XmN orientation, XmHORIZONTAL,
            XmN packing, XmPACK_TIGHT,
        |# ) ->> gallery -> layout_window.rlw_galleryarea;

    add_gallery_buttons(gallery_buttons, gallery)
        -> layout_window.rlw_gallerybuttons;


    lvars footer;
    XtVaCreateManagedWidget('status', xmTextFieldWidget, form,
        #|
            XmN bottomAttachment, XmATTACH_FORM,
            XmN leftAttachment, XmATTACH_FORM,
            XmN rightAttachment, XmATTACH_FORM,
            XmN editable, true,
            XmN columns, 60,
            ;;; XmN blinkRate, 0,
            ;;; XmN cursorPositionVisible, false,
/*
#_IF DEFV XLINK_VERSION < 1002
            XmN traversalOn, true,
#_ELSE
            XmN traversalOn, false,
#_ENDIF
*/
            XmN marginWidth, 1,
            XmN marginHeight, 1,
        |#) ->> footer -> layout_window.rlw_footer;

    lvars scroller;
    XtVaCreateManagedWidget('scrollpane', xmScrolledWindowWidget, form,
        #|
            XmN width, 200,
            XmN height, 200,
            XmN scrollingPolicy, XmAUTOMATIC,
            XmN scrollBarPlacement, XmBOTTOM_RIGHT,
            XmN leftAttachment, XmATTACH_FORM,
            XmN rightAttachment, XmATTACH_FORM,
            XmN topAttachment, XmATTACH_WIDGET,
            XmN topWidget, gallery,
            XmN bottomAttachment, XmATTACH_WIDGET,
            XmN bottomWidget, footer,
        |# ) ->> scroller -> layout_window.rlw_scrollarea;

    lvars composite;
    XtVaCreateManagedWidget('composite', xpwCompositeWidget, scroller,
        #|
            XmN width, 800,
            XmN height, 800,
        |# ) ->> composite -> layout_window.rlw_composite;

    lvars graphic;
    XtVaCreateManagedWidget('drawing', xpwGraphicWidget, composite,
        #|
            XmN width, 800,
            XmN height, 800,
        |# ) ->> graphic -> layout_window.rlw_drawarea;

    ClearFooter(layout_window);

    false -> XptVal shell(XmN allowShellResize:XptBoolean);

    XtAddCallback(shell, XtN popdownCallback, NotifyClose, layout_window);
enddefine;



vars
  CHARWIDTH
  CHARHEIGHT;

vars
 janela_graf;

7  -> CHARWIDTH;
13 -> CHARHEIGHT;



define draw_tree(temp_str , window);
lvars
  i, line, window, temp_str, font_name;

  1 -> line;
  applist([%
            while (issubstring('\n' , temp_str) ->> i) and (length(temp_str) > 1) do
              substring(1 , i-1 , temp_str);
              substring(i+1 , length(temp_str)-i , temp_str) -> temp_str;
            endwhile;
          %] ,
          procedure(str_item);
            lconstant
               arrow_gap_X = 4.0,
               arrow_gap_Y = 12.0;
            lvars
               str_col, temp_str_col, x_pix, y_pix;
            XpwDrawImageString(window, 1 , line*CHARHEIGHT , str_item);
               0 -> str_col;
               while (issubstring(consstring(23,1),str_item) ->> temp_str_col) then
                  str_col + temp_str_col -> str_col;
                  CHARWIDTH*str_col-3 -> x_pix;
                  CHARHEIGHT*line-2 -> y_pix;
                  XpwFillPolygon(window,
                          [%
                            round(x_pix-arrow_gap_X),
                            round(y_pix-arrow_gap_Y),
                            round(x_pix+arrow_gap_X),
                            round(y_pix-arrow_gap_Y),
                            round(x_pix),
                            round(y_pix)
                          %],
                          Convex,
                          CoordModeOrigin);
                  substring(temp_str_col+1 , length(str_item)-temp_str_col , str_item) -> str_item;
               endwhile;
            line + 1 -> line
          endprocedure);

enddefine;





define calcula_coordenadas(arv);
  lvars
   arv cadeia_carac;

  tree_to_string(arv) -> cadeia_carac;

enddefine;


define redesenha_arvore(arv);
  lvars
   arv cadeia_carac;

  tree_to_string(arv) -> cadeia_carac;
  XpwClearWindow(janela_graf);
  draw_tree(cadeia_carac, janela_graf);

enddefine;


;;; ---------------------------------------------



if vedsetupdone then
    ;;; vedputmessage('Loading first part of showtree');
endif;

/* ------------------------------------------------------------------------ */
/*      INITIALISATIONS                                                     */
/* ------------------------------------------------------------------------ */

if systrmdev(popdevin) then
   ;;; probably not needed any more
   vedsetup();     ;;; make sure vedinit.p file has been compiled
endif;

uses graphcharsetup;
uses drawline;


section $-tree_to_string => node_location node_daughters node_draw_data
    subtree_rootnode_name showtreename vgap isleaf root daughters
    showtreedefaults showtreeinit name_&_subtrees width height box
    draw_node tree_printable tree_graphical mid nodes_coords node_label
    file_to_string tree_to_string;


/* ------------------------------------------------------------------------ */
/* DECLARATIONS OF THINGS THAT USERS MIGHT WANT TO ACCESS (but not redefine)*/
/* ------------------------------------------------------------------------ */

/* three vedfileprops containing properties mapping node names to: */
global vars
    node_location = newvedfileprop(),   ;;; [startrow finishrow startcol finishcol]
    node_daughters = newvedfileprop(),  ;;; list of daughter node identifiers
    node_draw_data = newvedfileprop(),  ;;; [?name ?startrow]
    subtree_rootnode_name = newvedfileprop(),   ;;; a property to give inverse
            ;;; mapping from tree fragments to node names. N.B. this will only
            ;;; work on sub-trees, not on leafs.
    ;

/* ------------------------------------------------------------------------ */
/*       SOME USER RE-DEFINABLE PROCEDURES AND VARIABLES (see help file)    */
/* ------------------------------------------------------------------------ */

global vars
    nodes_coords = [],          ;;; List of coordinates of both top left and
                                ;;; bottom right hand corners of all nodes.

    node_label = '',            ;;; Name of the current tree node.

    showtreename = 'tree.t',
    vgap = 1,                   ;;; Vertical spacing between nodes
procedure(
    isleaf = atom,
    root = hd,
    daughters = tl,
    showtreedefaults = vedhelpdefaults,
    showtreeinit = identfn,
)
    ;

define global name_&_subtrees(tree) -> name -> subtrees;
lvars tree name subtrees;
    ;;; tree is not a leaf, but may have no daughters
    root(tree) -> name;
    unless isstring(name) or isword(name) do
        unless isleaf(name) do
            datalist(tree) -> subtrees;
            space -> name
        else
            name >< '' -> name;
            daughters(tree) -> subtrees
        endunless
    else
        daughters(tree) -> subtrees
    endunless
enddefine;

define global width(node, name);
lvars node name;
    unless isword(name) or isstring(name) do name >< '' -> name endunless;
    if node_daughters()(node) then
        length(name) + 2
    else
        length(name)
    endif
enddefine;

define global height(node, name);
lvars node name;
    3
enddefine;



define global box(x1, y1, x2, y2);
lvars x1 y1 x2 y2;

[ ^^nodes_coords [^node_label [^x1 ^y1 ^(x2+2) ^y2] ] ] -> nodes_coords;

    drawline(x1, y1, x2, y1);
    drawline(x1, y1, x1, y2);
    drawline(x1, y2, x2, y2);
    drawline(x2, y1, x2, y2);
enddefine;



define global draw_node(node, val);
lvars node val name r1 c1 r2 c2;
    ;;; val --> [?r1 ?r2 ?c1 ?c2]; but matches won't work with lvars
    dl(val) -> c2 -> c1 -> r2 -> r1;
    hd(node_draw_data()(node)) >< '' -> name;
    if node_daughters()(node) then
        name -> node_label;
        box(c1, r1, c2-2, r2);
        c1 + 1 -> c1
    endif;
    vedjumpto(r1 + 1, c1);
    vedinsertstring(name)
enddefine;




define file_to_string();
lvars i, line, temp_str1;

   vedtopfile();

    consstring(#|
        until vedatend() do
            explode(vedthisline());
            `\n`;
            vedchardown();
        enduntil;
    |#) ->temp_str1;


    ;;; FOR POP-VERSION  14.2
    ;;; Just change CHARS according to the table below:
    ;;;   11  12  13  14  15  18  23  24  25
    ;;;  134 138 137 133 143 131 135 139 140

    fast_for i from 1 to length(temp_str1) do
      if subscrs(i , temp_str1) = 134 then
         11 -> subscrs(i , temp_str1);
      elseif subscrs(i , temp_str1) = 138 then
         12 -> subscrs(i , temp_str1);
      elseif subscrs(i , temp_str1) = 137 then
         13 -> subscrs(i , temp_str1);
      elseif subscrs(i , temp_str1) = 133 then
         14 -> subscrs(i , temp_str1);
      elseif subscrs(i , temp_str1) = 143 then
         15 -> subscrs(i , temp_str1);
      elseif subscrs(i , temp_str1) = 131 then
         18 -> subscrs(i , temp_str1);
      elseif subscrs(i , temp_str1) = 135 then
         23 -> subscrs(i , temp_str1);
      elseif subscrs(i , temp_str1) = 139 then
         24 -> subscrs(i , temp_str1);
      elseif subscrs(i , temp_str1) = 140 then
         25 -> subscrs(i , temp_str1);
      endif;
    endfast_for;

    temp_str1;

    ved_rrq();
enddefine;







/* ------------------------------------------------------------------------ */
/* PROCEDURES THAT CALCULATE THE LAYOUT OF THE TREE ON THE SCREEN           */
/* ------------------------------------------------------------------------ */

vars procedure(
    shapetree,
    nodename = gensym(%"node"%),
    )
    ;

define transformtree(tree, depth) -> topnode;
lvars tree depth topnode name subtrees;
    nodename() -> topnode;
    if isleaf(tree) then
        [^tree ^depth] -> node_draw_data()(topnode);
    else
        topnode -> subtree_rootnode_name()(tree);     ;;; in case other progs want to modify the tree
        name_&_subtrees(tree) -> name -> subtrees;
        [^name ^depth] -> node_draw_data()(topnode);
        maplist(subtrees,
            transformtree(% depth + vgap + height(topnode,name) %))
            -> subtrees;
        subtrees -> node_daughters()(topnode);
    endif
enddefine;

define rhsofleftneighbour(r1, r2) -> rhs;
lvars r1 r2 rhs;
    1 -> rhs;
    appproperty(node_location(),
        procedure(x, val);
        lvars x val s1 s2 c2;
            ;;; val --> [?s1 ?s2 = ?c2];
            dl(val) -> c2 ->; -> s2 -> s1;
            if r2 >= s1 and r1 <= s2 then
                if c2 >= rhs then c2 + 1 -> rhs endif
            endif
        endprocedure);
enddefine;

define movesubtree(node, r);
lvars node r subnodes r1 r2 c1 c2;
    if (node_daughters()(node) ->> subnodes)  then
        applist(subnodes, movesubtree(% r %))
    endif;
    ;;; node_location()(node) --> [?r1 ?r2 ?c1 ?c2];
    dl(node_location()(node)) -> c2 -> c1 -> r2 -> r1;
    [%r1, r2, c1 + r, c2 + r %] -> node_location()(node);
enddefine;

define global mid(c1, c2);
lvars c1 c2;
    intof((c1 + c2 - 2) / 2)
enddefine;

define centreofsubnodes(node, name) -> c1 -> c2;
lvars node name subnodes r w c1 c2;
    width(node, name) -> w;
    if (node_daughters()(node) ->> subnodes) and subnodes /== [] then
        applist(subnodes, shapetree);
        ;;; node_location()(front(subnodes)) --> [= = ?c1 =];
        node_location()(front(subnodes))(3) -> c1;
        last(subnodes) -> node;
        ;;; node_location()(node) -->  [= = = ?r];
        node_location()(node)(4) -> r;
        mid(r, c1) - intof((w - 1)/2) -> c1
    else
        1 -> c1;
    endif;
    c1 + w + 1 -> c2
enddefine;

define shapetree(node);
lvars node r1 r2 c1 c2 rhs name;
    ;;; node_draw_data()(node) -->  [?name ?r1];
    dl(node_draw_data()(node)) -> r1 -> name;
    r1 + height(node, name) - 1 -> r2;
    centreofsubnodes(node, name) -> c1 -> c2;
    rhsofleftneighbour(r1 - round(vgap/2), r2 + round(vgap/2)) -> rhs;
    [^r1 ^r2 ^c1 ^c2] -> node_location()(node);
    if rhs > c1 then movesubtree(node, rhs-c1) endif;
enddefine;

if vedsetupdone then
   ;;; vedputmessage('Loading second part of showtree');
endif;

/* ------------------------------------------------------------------------ */
/* PROCEDURES TO DRAW THE TREE ACCORDING TO THE CALCULATED LAYOUT           */
/* ------------------------------------------------------------------------ */

define straightjoin(node, unode);
lvars node unode r1 r2 c1 c2;
    ;;; node_location()(node) --> [= ?r2 ?c1 ?c2];
    dl(tl(node_location()(node))) -> c2 -> c1 -> r2;
    mid(c1, c2) -> c1;
    ;;; node_location()(unode) --> [?r1 = = =];
    hd(node_location()(unode)) -> r1;
    drawline(c1, r2, c1, r1)
enddefine;

define sidejoin(node, unode, left);
lvars node unode left r1 r2 c1 c2 ct rmid;
    ;;; node_location()(node) --> [= ?r2 ?c1 ?c2];
    dl(tl(node_location()(node))) -> c2 -> c1 -> r2;
    mid(c1,c2) -> ct;
    ;;; node_location()(unode) --> [?r1 = ?c1 ?c2];
    dl(node_location()(unode)) -> c2 -> c1 ->; -> r1;
    mid(c1, c2) -> c1;
    round((r1 + r2) / 2) -> rmid;
    if left then drawline(ct, r2, ct, rmid) endif;
    drawline(ct, rmid, c1, rmid);
    drawline(c1, rmid, c1, r1);
enddefine;

vars procedure(
    leftjoin = sidejoin(%true%),
    rightjoin = sidejoin(%false%),
    );

define underjoin(node, subnodes);
lvars node unode subnodes r1 c1 c2 r2 rmid;
    ;;; node_location()(node) --> [= ?r2 ==];
    node_location()(node)(2) -> r2;
    for unode in subnodes do
        ;;; node_location()(unode) --> [?r1 = ?c1 ?c2];
        dl(node_location()(unode)) -> c2 -> c1 ->; -> r1;
        round((r1 + r2) / 2) -> rmid;
        mid(c1, c2) -> c1;
        drawline(c1, r1, c1, rmid)
    endfor
enddefine;

define connectup();
    appproperty(node_daughters(),
        procedure(node,val);
        lvars val node unode subnodes;
            ;;; if val matches [?unode ??subnodes] then
            if listlength(val) > 0 then
                dest(val) -> subnodes -> unode;
                if subnodes == [] then
                    straightjoin(node, unode)
                else
                    leftjoin(node, unode);
                    ;;; subnodes --> [??subnodes ?unode];
                    last(subnodes) -> unode;
                    allbutlast(1, subnodes) -> subnodes;
                    rightjoin(node, unode);
                    underjoin(node, subnodes)
                endif
            endif
        endprocedure);
enddefine;

/* ------------------------------------------------------------------------ */
/* MISCELLANEOUS UTILITY PROCEDURES AND MAIN PROCEDURES                      */
/* ------------------------------------------------------------------------ */

define global tree_printable();
    Graphcharsetup("print");
    true -> graphcharsetupdone;     ;;; prevent it being redone
    5 -> vgap
enddefine;

define global tree_graphical();
    Graphcharsetup(vedterminalname);
    4 -> vgap
enddefine;



define global tree_to_string(tree);
    lvars tree node name row col oldwindow = vedstartwindow,
            oldchanged = vedchanged;
    dlocal vedstatic database = [], vedinitfile vedautowrite = false,
            vedstartwindow = vedscreenlength;


    graphcharsetup();               /* ensure graphic vars are set up */

    vedsetup();

    1 -> gensym("node");

    [] -> nodes_coords;
    '' -> node_label;

    procedure(oldvedini,flag);
        lvars oldvedini flag;
        dlocal vedediting;

        oldvedini -> vedinitfile;

        if vedcurrent = showtreename then

            vedscreenclear();
            ;;; vedputmessage('Please Wait - Planning the layout');
            showtreeinit();
            newproperty([], 59, false, true) -> node_location();
            newproperty([], 59, false, true) -> node_daughters();
            newproperty([], 59, false, true) -> node_draw_data();
            newproperty([], 59, false, true) -> subtree_rootnode_name();
            oldwindow -> vedstartwindow;
            true -> vedstatic;
            false ->> vedchanged -> vedediting;
            ved_clear();
            shapetree(transformtree(tree,1));
            procedure();
                dlocal vedediting = true;
                ;;; vedputmessage('Please Wait - Drawing the graph')
            endprocedure();
            appproperty(node_location(), draw_node);
            connectup();
            ;;; node_location()("node1") --> [= = ?col =];
            node_location()("node1")(3) -> col;
            vedjumpto(1, col);
            true -> vedediting;
            if flag then vedrefresh(); endif;
        endif;


        vedinitfile();
        file_to_string();

    endprocedure(% vedinitfile, vedediting and vedcurrent = showtreename %) -> vedinitfile;

    vededitor(showtreedefaults, showtreename);

enddefine;


endsection;     ;;; $-tree_to_string


;;; ---------------------------------------------


vars
  node_name coords_node_name ;


define video_reverso(node_name1 , x1, y1 , x2 , y2);
 lvars
   node_name1 x1 y1  x2  y2 bck_colour frg_colour;

  ''><node_name1 -> node_name1;

  XptValue(janela_graf , XtN foreground) -> frg_colour;
  XptValue(janela_graf , XtN background) -> bck_colour;

  XpwFillRectangle(janela_graf, (x1*CHARWIDTH)+2-(CHARWIDTH div 3) ,
                         (y1*CHARHEIGHT)+3-(CHARHEIGHT div 3) ,
                         length(node_name1)*CHARWIDTH+2*(CHARWIDTH div 3)-2 ,
                         CHARHEIGHT+2*(CHARHEIGHT div 3)+1                 );

  bck_colour -> XptValue(janela_graf , XtN foreground);
  XpwDrawString(janela_graf , (x1*CHARWIDTH)+1 , (y1+1)*CHARHEIGHT , node_name1);
  frg_colour -> XptValue(janela_graf , XtN foreground);
enddefine;




define video_normal(node_name1, x1, y1 , x2 , y2);
 lvars
   node_name1 x1 y1  x2  y2 bck_colour frg_colour;

  ''><node_name1 -> node_name1;

  XptValue(janela_graf , XtN foreground) -> frg_colour;
  XptValue(janela_graf , XtN background) -> bck_colour;

  bck_colour -> XptValue(janela_graf , XtN foreground);
  XpwFillRectangle(janela_graf , (x1*CHARWIDTH)+2-(CHARWIDTH div 3) ,
                         (y1*CHARHEIGHT)+3-(CHARHEIGHT div 3) ,
                         length(node_name1)*CHARWIDTH+2*(CHARWIDTH div 3)-2 ,
                         CHARHEIGHT+2*(CHARHEIGHT div 3)+1                 );
  frg_colour -> XptValue(janela_graf , XtN foreground);

  ;;; XpwDrawImageString(janela_graf , (x1*CHARWIDTH)+1 , (y1+1)*CHARHEIGHT , node_name1);
  XpwDrawString(janela_graf , (x1*CHARWIDTH)+1 , (y1+1)*CHARHEIGHT , node_name1);
enddefine;




define rui_before(point1 , point2 , dimension);

  switchon dimension
     case = "X_axis" then
          (point1-1)*CHARWIDTH < point2;

     case = "Y_axis" then
          (point1-1)*CHARHEIGHT < point2;
  endswitchon;
enddefine;





define rui_after(point1 , point2 , dimension);

  switchon dimension
     case = "X_axis" then
          (point1-2)*CHARWIDTH > point2;

     case = "Y_axis" then
          point1*CHARHEIGHT > point2;
  endswitchon;
enddefine;




define tree_node_pressed(wid , item , press_release1);
  vars
    wid
    item
    press_release1
    x_mouse
    y_mouse
    xsize
    ysize
    x1
    y1
    x2
    y2;


  ;;; Ignore "RELEASE" button.
  if (exacc ^int press_release1 ->> press_release1) >= 0  then

    XptValue(wid,XtN mouseX) -> x_mouse;
    XptValue(wid,XtN mouseY) -> y_mouse;

    ;;; destvector(rui.w_size) ->;
         400 -> ysize;
         400 -> xsize;

    consword('') -> node_name;
    [] -> coords_node_name;

    if                   nodes_coords
                            matches
       [  ==  [ ?node_name [ ?x1: % rui_before(%x_mouse,"X_axis"%) %
                             ?y1: % rui_before(%y_mouse,"Y_axis"%) %
                             ?x2: % rui_after (%x_mouse,"X_axis"%) %
                             ?y2: % rui_after (%y_mouse,"Y_axis"%) %  ]  ]  ==  ]
    then
       [^x1 ^y1 ^x2 ^y2] -> coords_node_name;

       video_reverso(node_name, x1, y1 , x2, y2);

       syssleep(30);

       video_normal(node_name , x1, y1 , x2, y2);

    else
       consword('') -> node_name;

    endif;

  endif;

enddefine;



define str_to_word(arv_str) -> arv_word;
  lvars
    itm arv_str arv_word;

  [%
   fast_for itm in arv_str do

    [ ^(consword(hd(itm)))  ^^(tl(itm)) ]

   endfast_for
  %] -> arv_word;

enddefine;



define monta_lista_coord(inp_struc_tree) -> out_struc_coord;
  lvars
    inp_struc_tree out_struc_coord;

  calcula_coordenadas(inp_struc_tree);
  str_to_word(nodes_coords) -> out_struc_coord;
  ;;; [% explode(nodes_coords) %] -> out_struc_coord;

enddefine;



;;; ---------------------------------------------

vars win = make_layout_window(
                file_menu_buttons,
                edit_menu_buttons,
                help_menu_buttons,
                false,
                gallery_buttons,
                false,
                pop_ui_control_panel
          );

DisplayWin(win);

win.rlw_drawarea -> janela_graf;

while not(XpwSetFont(janela_graf, '7x13bold')) do
endwhile;

ClearDrawing(win);

XtRemoveAllCallbacks(janela_graf, XtN buttonEvent);
XtAddCallback(janela_graf, XtN buttonEvent ,
              tree_node_pressed , 1);

false -> pop_character_set;
