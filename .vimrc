set nocompatible
filetype off

" Set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim

" Download plug-ins to the ~/.vim/plugged/ directory
call vundle#begin('~/.vim/plugged')

" Let Vundle manage Vundle
Plugin 'VundleVim/Vundle.vim'
Plugin 'sheerun/vim-polyglot'
Plugin 'kristijanhusak/vim-hybrid-material'
Plugin 'scheakur/vim-scheakur'
Plugin 'jiangmiao/auto-pairs'
Plugin 'preservim/nerdtree'
Plugin 'preservim/tagbar'
Plugin 'dyng/ctrlsf.vim'
Plugin 'derekwyatt/vim-fswitch'
Plugin 'derekwyatt/vim-protodef'
Plugin 'Yggdroot/indentLine'
Plugin 'justinmk/vim-sneak'
Plugin 'phanviet/vim-monokai-pro'
Plugin 'easymotion/vim-easymotion'
Plugin 'stevearc/vim-arduino'
Plugin 'normen/vim-pio'
call vundle#end()

filetype plugin indent on

au! BufEnter *.cpp let b:fswitchdst = 'hpp,h'
au! BufEnter *.h let b:fswitchdst = 'cpp,c'
nmap <C-Z> :vsplit <bar> :wincmd l <bar> :FSRight<CR>

set nu     " Enable line numbers
syntax on  " Enable syntax highlighting

" How many columns of whitespace a \t is worth
set tabstop=4 

" How many columns of whitespace a "level of indentation" is worth

set shiftwidth=4 " Use spaces when tabbing
set expandtab

set incsearch  " Enable incremental search
set hlsearch   " Enable highlight search

set termwinsize=12x0   " Set terminal size
set splitbelow         " Always split below
set mouse=a            " Enable mouse drag on window splits

let g:enable_bold_font = 1
let g:enable_italic_font = 1
let g:AutoPairsShortcutToggle = '<C-P>' " auto-pair shortcut in normal mode

let NERDTreeShowBookmarks = 1   " Show the bookmarks table
let NERDTreeShowHidden = 1      " Show hidden files
let NERDTreeShowLineNumbers = 0 " Hide line numbers
let NERDTreeMinimalMenu = 1     " Use the minimal menu (m)
let NERDTreeWinPos = 'left'     " Panel opens on the left side
let NERDTreeWinSize = 31        " Set panel width to 31 columns
nmap <F2> :NERDTreeToggle<CR>

" Focus the panel when opening it
let g:tagbar_autofocus = 1" Highlight the active tag
let g:tagbar_autoshowtag = 1" Make panel vertical and place on the right
let g:tagbar_position = 'botright vertical'" Mapping to open and close the panel
nmap <F8> :TagbarToggle<CR>

" Use the ack tool as the backend
let g:ctrlsf_backend = 'ack' " Auto close the results panel when opening a file
let g:ctrlsf_auto_close = { "normal":0, "compact":0 } " Immediately switch focus to the search window
let g:ctrlsf_auto_focus = { "at":"start" } " Don't open the preview window automatically
let g:ctrlsf_auto_preview = 0 " Use the smart case sensitivity search scheme
let g:ctrlsf_case_sensitive = 'smart' " Normal mode, not compact mode
let g:ctrlsf_default_view = 'normal' " Use absoulte search by default
let g:ctrlsf_regex_pattern = 0 " Position of the search window
let g:ctrlsf_position = 'right' " Width or height of search window
let g:ctrlsf_winsize = '46' " Search from the current working directory
let g:ctrlsf_default_root = 'cwd'

" (Ctrl+F) Open search prompt (Normal Mode)
nmap <C-F>f <Plug>CtrlSFPrompt 
" (Ctrl-F + f) Open search prompt with selection (Visual Mode)
xmap <C-F>f <Plug>CtrlSFVwordPath
" (Ctrl-F + F) Perform search with selection (Visual Mode)
xmap <C-F>F <Plug>CtrlSFVwordExec
" (Ctrl-F + n) Open search prompt with current word (Normal Mode)
nmap <C-F>n <Plug>CtrlSFCwordPath
" (Ctrl-F + o )Open CtrlSF window (Normal Mode)
nnoremap <C-F>o :CtrlSFOpen<CR>
" (Ctrl-F + t) Toggle CtrlSF window (Normal Mode)
nnoremap <C-F>t :CtrlSFToggle<CR>
" (Ctrl-F + t) Toggle CtrlSF window (Insert Mode)
inoremap <C-F>t <Esc>:CtrlSFToggle<CR>

" Use ctrl-[hjkl] to select the active split!
nmap <silent> <c-k> :wincmd k<CR>
nmap <silent> <c-j> :wincmd j<CR>
nmap <silent> <c-h> :wincmd h<CR>
nmap <silent> <c-l> :wincmd l<CR>



" Pull in prototypes
nmap <buffer> <silent> <leader> ,PP
" Pull in prototypes without namespace definition"
nmap <buffer> <silent> <leader> ,PN
if (has("termguicolors"))
  set termguicolors
endif

set background=dark
colorscheme monokai_pro
imap jk <Esc>
