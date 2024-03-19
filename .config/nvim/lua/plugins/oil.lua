return {
  "stevearc/oil.nvim",
  enabled = false,
  opts = {},
  -- Optional dependencies
  dependencies = { "nvim-tree/nvim-web-devicons" },
  config = function()
    require("oil").setup({})
  end,
}
