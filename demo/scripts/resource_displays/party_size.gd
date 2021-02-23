extends PanelContainer


onready var current_size_line_edit: = $VBoxContainer/HBoxContainer/CurrentSize/LineEdit
onready var max_size_line_edit: = $VBoxContainer/HBoxContainer/MaxSize/LineEdit

var party_size: Discord.PartySize setget set_party_size


func set_party_size(new_party_size: Discord.PartySize) -> void:
	if new_party_size:
		current_size_line_edit.text = str(new_party_size.current_size)
		max_size_line_edit.text = str(new_party_size.max_size)
