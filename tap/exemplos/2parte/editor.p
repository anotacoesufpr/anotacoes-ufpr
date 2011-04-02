
2e6 -> popmemlim;

exload_batch;

uses-now Xm;
uses-now Xpw;

loadinclude xpt_coretypes.ph;
loadinclude XmConstants.ph;

loadinclude XpwPixmap;

uses switchon;

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
            XtN title, 'Editor Grafico',
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



;;; ---------------------------------------------
;;;    PROCEDURES TO MANAGE GRAPHICAL ITEMS
;;; ---------------------------------------------

vars
  CHARWIDTH
  CHARHEIGHT
  janela_graf
  nodes_coords  ;;; List of coordinates of both top left and bottom right hand corners of all nodes.
  node_label  ;;; Name of the current tree node.
  node_name
  coords_node_name
;

;;; 7  -> CHARWIDTH;
9  -> CHARWIDTH;
;;; 13 -> CHARHEIGHT;
15 -> CHARHEIGHT;
[] -> nodes_coords;
'' -> node_label;

define desenha_nodo(node_name1, x, y);
  lvars
    node_name1 x y bck_colour frg_colour;
  ''><node_name1 -> node_name1;
  XptValue(janela_graf , XtN foreground) -> frg_colour;
  XptValue(janela_graf , XtN background) -> bck_colour;
  XpwFillRectangle(janela_graf, x, y, length(node_name1)*CHARWIDTH+4, CHARHEIGHT+4);
  bck_colour -> XptValue(janela_graf , XtN foreground);
  XpwDrawString(janela_graf, x+2, y+CHARHEIGHT-1, node_name1);
  frg_colour -> XptValue(janela_graf , XtN foreground);
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

;;; while not(XpwSetFont(janela_graf, '7x13bold')) do
while not(XpwSetFont(janela_graf, '9x15bold')) do
endwhile;

ClearDrawing(win);

define limpa_tela();
  ClearDrawing(win);
enddefine;

define desenha_linha_com_espessura(x1, y1, x2, y2, L);
  lvars x1 y1 x2 y2 L;
  if isinteger(L) then
    L -> XptValue(janela_graf, XtN lineWidth,"int");
    XpwDrawLine(janela_graf, x1, y1, x2, y2);
  endif;
enddefine;

define escreve_peso_aresta(valor, x, y);
  lvars valor x y;
  if isnumber(valor) then
    '' >< round(valor) -> valor;
    XpwDrawString(janela_graf, round(x), round(y), valor);
  endif;
enddefine;
