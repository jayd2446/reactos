
#include "pch.h"

#include "rbuild.h"

using std::string;

Exception::Exception ()
{
}

Exception::Exception ( const string& message )
{
	Message = message;
}

Exception::Exception ( const char* format,
                       ...)
{
	va_list args;
	va_start ( args,
	           format);
	Message = ssvprintf ( format,
	                      args);
	va_end ( args );
}

void Exception::SetMessage ( const char* message,
                             va_list args)
{
	Message = ssvprintf ( message,
	                      args);
}


InvalidOperationException::InvalidOperationException ( const char* filename,
	                                                   const int linenumber)
{
	Message = ssprintf ( "%s:%d",
	                     filename,
	                     linenumber );
}


FileNotFoundException::FileNotFoundException ( const string& filename )
	: Exception ( "File '%s' not found.",
	              filename.c_str() )
{
	Filename = filename;
}


AccessDeniedException::AccessDeniedException ( const string& filename)
	: Exception ( "Access denied to file '%s'.",
	             filename.c_str() )
{
	Filename = filename;
}


InvalidBuildFileException::InvalidBuildFileException ( const string& location,
                                                       const char* message,
                                                       ...)
{
	va_list args;
	va_start ( args,
	           message );
	SetLocationMessage ( location, message, args );
	va_end ( args );
}

InvalidBuildFileException::InvalidBuildFileException ()
{
}

void
InvalidBuildFileException::SetLocationMessage ( const std::string& location,
                                                const char* message,
                                                va_list args )
{
	Message = location + ": " + ssvprintf ( message, args );
}

XMLSyntaxErrorException::XMLSyntaxErrorException ( const string& location,
	                                               const char* message,
	                                               ... )
{
	va_list args;
	va_start ( args,
	          message );
	SetLocationMessage ( location, message, args );
	va_end ( args );
}


RequiredAttributeNotFoundException::RequiredAttributeNotFoundException ( const string& attributeName,
                                                                         const string& elementName )
	: InvalidBuildFileException ( "Required attribute '%s' not found on '%s'.",
	                              attributeName.c_str (),
	                              elementName.c_str ())
{
}

InvalidAttributeValueException::InvalidAttributeValueException ( const string& name,
	                                                             const string& value )
	: InvalidBuildFileException ( "Attribute '%s' has an invalid value '%s'.",
	                              name.c_str (),
	                              value.c_str () )
{
	
}

BackendNameConflictException::BackendNameConflictException ( const string& name )
	: Exception ( "Backend name conflict: '%s'",
	             name.c_str() )
{
}


UnknownBackendException::UnknownBackendException ( const string& name )
	: Exception ( "Unknown Backend requested: '%s'",
	             name.c_str() )
{
}

UnknownModuleTypeException::UnknownModuleTypeException ( const string& moduletype )
	: Exception ( "module type requested: '%s'",
	              moduletype.c_str() )
{
}
