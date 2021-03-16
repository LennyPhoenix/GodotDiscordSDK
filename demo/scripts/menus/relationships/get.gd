extends PanelContainer


onready var id_line_edit: = $VBoxContainer/MarginContainer/VBoxContainer/InputFields/VBoxContainer/UserID
onready var result_line_edit: = $VBoxContainer/MarginContainer/VBoxContainer/OutputFields/VBoxContainer/Result/LineEdit
onready var relationship_info: = $VBoxContainer/MarginContainer/VBoxContainer/OutputFields/VBoxContainer/Relationship


func _on_button_down() -> void:
	var id: String = id_line_edit.text

	DiscordManager.relationships.get(id)
	var ret: Array = yield(DiscordManager.relationships, "get_callback")
	var result: int = ret[0]
	var relationship: Discord.Relationship = ret[1]

	result_line_edit.text = DiscordManager.enum_to_string(Discord.Result, result)
	relationship_info.relationship = relationship
