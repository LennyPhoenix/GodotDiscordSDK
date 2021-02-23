extends PanelContainer


onready var current_size_line_edit: = $VBoxContainer/HBoxContainer/CurrentSize
onready var max_size_line_edit: = $VBoxContainer/HBoxContainer/MaxSize


func get_party_size() -> Discord.PartySize:
	var size: = Discord.PartySize.new()
	size.current_size = int(current_size_line_edit.text)
	size.max_size = int(max_size_line_edit.text)
	return size
