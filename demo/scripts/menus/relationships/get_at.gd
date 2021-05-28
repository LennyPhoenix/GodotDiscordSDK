extends PanelContainer

onready var index_line_edit := $VBoxContainer/MarginContainer/VBoxContainer/InputFields/VBoxContainer/Index
onready var result_line_edit := $VBoxContainer/MarginContainer/VBoxContainer/OutputFields/VBoxContainer/Result/LineEdit
onready var relationship_info := $VBoxContainer/MarginContainer/VBoxContainer/OutputFields/VBoxContainer/Relationship


func _on_button_down() -> void:
	var index := int(index_line_edit.text)

	DiscordManager.relationships.get_at(index)
	var ret: Array = yield(DiscordManager.relationships, "get_at_callback")
	var result: int = ret[0]
	var relationship: Discord.Relationship = ret[1]

	result_line_edit.text = DiscordManager.enum_to_string(Discord.Result, result)
	relationship_info.relationship = relationship
