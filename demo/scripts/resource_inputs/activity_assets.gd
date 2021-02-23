extends PanelContainer


onready var large_image_line_edit: = $VBoxContainer/Large/Image
onready var large_text_line_edit: = $VBoxContainer/Large/Text
onready var small_image_line_edit: = $VBoxContainer/Small/Image
onready var small_text_line_edit: = $VBoxContainer/Small/Text


func get_assets() -> Discord.ActivityAssets:
	var assets: = Discord.ActivityAssets.new()
	assets.large_image = large_image_line_edit.text
	assets.large_text = large_text_line_edit.text
	assets.small_image = small_image_line_edit.text
	assets.small_text = small_text_line_edit.text
	return assets
