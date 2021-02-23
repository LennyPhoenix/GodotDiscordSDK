extends PanelContainer


onready var large_image_line_edit: = $VBoxContainer/Large/Image/LineEdit
onready var large_text_line_edit: = $VBoxContainer/Large/Text/LineEdit
onready var small_image_line_edit: = $VBoxContainer/Small/Image/LineEdit
onready var small_text_line_edit: = $VBoxContainer/Small/Text/LineEdit

var assets: Discord.ActivityAssets setget set_assets


func set_assets(new_assets: Discord.ActivityAssets) -> void:
	if new_assets:
		large_image_line_edit.text = new_assets.large_image
		large_text_line_edit.text = new_assets.large_text
		small_image_line_edit.text = new_assets.small_image
		small_text_line_edit.text = new_assets.small_text
