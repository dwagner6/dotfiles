return {
  "max397574/better-escape.nvim",
  config = function()
    require("better_escape").setup({
      mapping = { "jk", "jj" }, -- a table with mappings to use
      timeout = vim.o.timeoutlen,
      clear_empty_lines = false,
      keys = "<Esc>",
    })
  end,
}
